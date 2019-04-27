#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/system_properties.h>
#include "sqlite3.h"
#include "device_database.h"

#define ARRAY_SIZE(n)	(sizeof (n) / sizeof (*(n)))

#define DEVICE_DATABASE_FILE            "device.db"

static const char *device_database_file_paths[] = {
  DEVICE_DATABASE_FILE,
  "/data/local/tmp/" DEVICE_DATABASE_FILE,
};

#define DEVICE_ID_REGISTER_START        10000
#define SLEEP_UTIME_FOR_BUSY            10000

#define SQL_QUERY_DEVICE \
  "SELECT device_id, check_property_name, check_property_value FROM supported_devices" \
  " WHERE (device = ?) AND (build_id = ?);"

#define SQL_QUERY_DEVICE_ADDRESS \
  "SELECT value FROM device_address WHERE (device_id = ?) AND (name = ?);"

#define SQL_QUERY_LAST_DEVICE_ID \
  "SELECT device_id FROM supported_devices ORDER BY device_id DESC;"

#define SQL_REGISTER_DEVICE \
  "INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value)" \
  " VALUES(?, ?, ?, ?, ?);"

#define SQL_REGISTER_DEVICE_ADDRESS \
  "INSERT INTO device_address(device_id, name, value) VALUES(?, ?, ?);"

#define IS_SQL_ERROR(rc) ((rc) != SQLITE_OK && (rc) != SQLITE_DONE && (rc) != SQLITE_ROW)


static sqlite3 *db;

static void
close_database(void)
{
  int i;
  int rc;

  if (!db) {
    return;
  }

  for (i = 0; i < 300; i++) {
    rc = sqlite3_close(db);

    if (rc == SQLITE_BUSY) {
      usleep(SLEEP_UTIME_FOR_BUSY);
      continue;
    }

    break;
  }

  if (IS_SQL_ERROR(rc)) {
    printf("%s(%d)\n", sqlite3_errmsg(db), sqlite3_errcode(db));
  }

  //printf("database is closed.\n");
}

static bool
init_database(void)
{
  int i;
  int rc;

  if (db != NULL) {
    return true;
  }

  for (i = 0; i < ARRAY_SIZE(device_database_file_paths); i++) {
    if (access(device_database_file_paths[i], R_OK | W_OK) == 0) {
      break;
    }
  }

  if (i == ARRAY_SIZE(device_database_file_paths)) {
    for (i = 0; i < ARRAY_SIZE(device_database_file_paths); i++) {
      printf("access failed: \"%s\"\n", device_database_file_paths[i]);
    }

    printf("\nFATAL ERROR: DB file open failed.\n");
    printf("Make sure install \"" DEVICE_DATABASE_FILE "\" from device_database!\n");
    exit(1);
  }

  rc = sqlite3_open(device_database_file_paths[i], &db);
  if (rc) {
    printf("Error = %d: sqlite3_open(): failed\n", rc);

    db = NULL;
    return false;
  }

  atexit(close_database);

  return true;
}

static int
execute_sql(sqlite3_stmt *st)
{
  int rc;

  while (true) {
    rc = sqlite3_step(st);
    if (rc == SQLITE_DONE) {
      break;
    }

    if (rc == SQLITE_BUSY) {
      usleep(SLEEP_UTIME_FOR_BUSY);
      continue;
    }

    if (rc == SQLITE_ROW) {
      break;
    }

    break;
  }

  return rc;
}


static device_id_t
register_device_id(const char *property_name)
{
  char device[PROP_VALUE_MAX];
  char build_id[PROP_VALUE_MAX];
  char buf[PROP_VALUE_MAX];
  const char *property_value;
  sqlite3_stmt *st;
  int rc;

  device_id_t device_id;

  if (!init_database()) {
    return DEVICE_NOT_SUPPORTED;
  }

  __system_property_get("ro.product.model", device);
  __system_property_get("ro.build.display.id", build_id);

  device_id = DEVICE_NOT_SUPPORTED;
  property_value = NULL;

  if (property_name) {
    __system_property_get(property_name, buf);
    property_value = buf;
  }

  rc = sqlite3_prepare(db, SQL_QUERY_LAST_DEVICE_ID, -1, &st, NULL);

  if (!IS_SQL_ERROR(rc)) {
    rc = sqlite3_reset(st);
  }

  if (!IS_SQL_ERROR(rc)) {
    for (rc = execute_sql(st); rc == SQLITE_ROW; rc = execute_sql(st)) {
      device_id = sqlite3_column_int(st, 0) + 1;
      if (device_id <= DEVICE_ID_REGISTER_START) {
        device_id = DEVICE_ID_REGISTER_START;
      }

      break;
    }
  }

  if (IS_SQL_ERROR(rc)) {
    printf("%s(%d)\n", sqlite3_errmsg(db), sqlite3_errcode(db));
    sqlite3_finalize(st);

    return DEVICE_NOT_SUPPORTED;
  }

  sqlite3_finalize(st);

  rc = sqlite3_prepare(db, SQL_REGISTER_DEVICE, -1, &st, NULL);

  if (!IS_SQL_ERROR(rc)) {
    rc = sqlite3_reset(st);
  }

  if (!IS_SQL_ERROR(rc)) {
    rc = sqlite3_bind_int(st, 1, device_id);
  }

  if (!IS_SQL_ERROR(rc)) {
    rc = sqlite3_bind_text(st, 2, device, -1, SQLITE_STATIC);
  }

  if (!IS_SQL_ERROR(rc)) {
    rc = sqlite3_bind_text(st, 3, build_id, -1, SQLITE_STATIC);
  }

  if (!IS_SQL_ERROR(rc)) {
    rc = sqlite3_bind_text(st, 4, property_name, -1, SQLITE_STATIC);
  }

  if (!IS_SQL_ERROR(rc)) {
    rc = sqlite3_bind_text(st, 5, property_value, -1, SQLITE_STATIC);
  }

  if (!IS_SQL_ERROR(rc)) {
    rc = execute_sql(st);
  }

  if (IS_SQL_ERROR(rc)) {
    printf("%s(%d)\n", sqlite3_errmsg(db), sqlite3_errcode(db));
    sqlite3_finalize(st);

    return DEVICE_NOT_SUPPORTED;
  }

  sqlite3_finalize(st);

  return device_id;
}

static device_id_t
get_device_id(bool do_regist)
{
  char device[PROP_VALUE_MAX];
  char build_id[PROP_VALUE_MAX];
  device_id_t device_id;
  const char *check_name;
  char name_buf[PROP_NAME_MAX];
  sqlite3_stmt *st;
  int rc;
  int i;

  if (!init_database()) {
    return DEVICE_NOT_SUPPORTED;
  }

  __system_property_get("ro.product.model", device);
  __system_property_get("ro.build.display.id", build_id);

  device_id = DEVICE_NOT_SUPPORTED;
  check_name = NULL;

  rc = sqlite3_prepare(db, SQL_QUERY_DEVICE, -1, &st, NULL);

  if (!IS_SQL_ERROR(rc)) {
    rc = sqlite3_reset(st);
  }

  if (!IS_SQL_ERROR(rc)) {
    rc = sqlite3_bind_text(st, 1, device, -1, SQLITE_STATIC);
  }

  if (!IS_SQL_ERROR(rc)) {
    rc = sqlite3_bind_text(st, 2, build_id, -1, SQLITE_STATIC);
  }

  if (!IS_SQL_ERROR(rc)) {
    for (rc = execute_sql(st); rc == SQLITE_ROW; rc = execute_sql(st)) {
      const char *check_value;

      device_id = sqlite3_column_int(st, 0);
      check_name = sqlite3_column_text(st, 1);
      check_value = sqlite3_column_text(st, 2);

      if (!check_name && !check_value) {
        break;
      }

      if (check_name && check_value) {
        char property_value[PROP_VALUE_MAX];

        __system_property_get(check_name, property_value);

        if (strcmp(property_value, check_value) == 0) {
          break;
        }

        strncpy(name_buf, check_name, sizeof (name_buf) - 1);
        name_buf[sizeof (name_buf) - 1] = '\0';

        check_name = name_buf;
      }

      device_id = DEVICE_NOT_SUPPORTED;
    }
  }

  if (IS_SQL_ERROR(rc)) {
    printf("%s(%d)\n", sqlite3_errmsg(db), sqlite3_errcode(db));

    sqlite3_finalize(st);

    return device_id;
  }

  sqlite3_finalize(st);

  if (!do_regist || device_id != DEVICE_NOT_SUPPORTED) {
    return device_id;
  }

  return register_device_id(check_name);
}

device_id_t
detect_device(void)
{
  return get_device_id(false);
}

unsigned long int
device_get_symbol_address(device_symbol_t symbol)
{
  device_id_t device_id;
  sqlite3_stmt *st;
  int rc;
  unsigned long int value;

  device_id = detect_device();
  if (device_id == DEVICE_NOT_SUPPORTED) {
    return 0;
  }

  value = 0;

  rc = sqlite3_prepare(db, SQL_QUERY_DEVICE_ADDRESS, -1, &st, NULL);

  if (!IS_SQL_ERROR(rc)) {
    rc = sqlite3_reset(st);
  }

  if (!IS_SQL_ERROR(rc)) {
    rc = sqlite3_bind_int(st, 1, device_id);
  }

  if (!IS_SQL_ERROR(rc)) {
    rc = sqlite3_bind_text(st, 2, symbol, -1, SQLITE_STATIC);
  }

  if (!IS_SQL_ERROR(rc)) {
    rc = execute_sql(st);
  }

  if (!IS_SQL_ERROR(rc)) {
    sqlite3_value *value_object;
    int value_type;
    value_object = sqlite3_column_value(st, 0);
    value_type = sqlite3_value_type(value_object);
    if (value_type == SQLITE_INTEGER) {
      value = sqlite3_value_int(value_object);
    } else {
      const unsigned char *value_text;
      value_text = sqlite3_value_text(value_object);
      if (value_text) {
        sscanf(value_text, "%lx", &value);
      }
    }
  }

  if (IS_SQL_ERROR(rc)) {
    printf("%s(%d)\n", sqlite3_errmsg(db), sqlite3_errcode(db));
  }

  sqlite3_finalize(st);

  return value;
}

bool
device_set_symbol_address(device_symbol_t symbol, unsigned long int address)
{
  device_id_t device_id;
  unsigned long int old;
  sqlite3_stmt *st;
  int rc;

  if (address == 0) {
    return false;
  }

  old = device_get_symbol_address(symbol);
  if (old == address) {
    return true;
  }

  if (old) {
    printf("Duplicate symbol \"%s\": old = 0x%08lx, new = 0x%08lx\n", symbol, old, address);
    return false;
  }

  device_id = get_device_id(true);

  rc = sqlite3_prepare(db, SQL_REGISTER_DEVICE_ADDRESS, -1, &st, NULL);

  if (!IS_SQL_ERROR(rc)) {
    rc = sqlite3_reset(st);
  }

  if (!IS_SQL_ERROR(rc)) {
    rc = sqlite3_bind_int(st, 1, device_id);
  }

  if (!IS_SQL_ERROR(rc)) {
    rc = sqlite3_bind_text(st, 2, symbol, -1, SQLITE_STATIC);
  }

  if (!IS_SQL_ERROR(rc)) {
    char hex_address[20] = { 0 };
    int length = snprintf(hex_address, sizeof(hex_address), "0x%08lx", address);
    rc = sqlite3_bind_text(st, 3, hex_address, length, SQLITE_STATIC);
  }

  if (!IS_SQL_ERROR(rc)) {
    rc = execute_sql(st);
  }

  if (IS_SQL_ERROR(rc)) {
    printf("%s(%d)\n", sqlite3_errmsg(db), sqlite3_errcode(db));
    sqlite3_finalize(st);

    return false;
  }

  sqlite3_finalize(st);

  return true;
}

void
print_reason_device_not_supported(void)
{
  char device[PROP_VALUE_MAX];
  char build_id[PROP_VALUE_MAX];
  const char *check_name;
  sqlite3_stmt *st;
  int rc;
  int i;

  if (!init_database()) {
    return;
  }

  __system_property_get("ro.product.model", device);
  __system_property_get("ro.build.display.id", build_id);

  check_name = NULL;

  rc = sqlite3_prepare(db, SQL_QUERY_DEVICE, -1, &st, NULL);

  if (!IS_SQL_ERROR(rc)) {
    rc = sqlite3_reset(st);
  }

  if (!IS_SQL_ERROR(rc)) {
    rc = sqlite3_bind_text(st, 1, device, -1, SQLITE_STATIC);
  }

  if (!IS_SQL_ERROR(rc)) {
    rc = sqlite3_bind_text(st, 2, build_id, -1, SQLITE_STATIC);
  }

  if (!IS_SQL_ERROR(rc)) {
    rc = execute_sql(st);
  }

  if (!IS_SQL_ERROR(rc)) {
    check_name = sqlite3_column_text(st, 1);
  }

  if (IS_SQL_ERROR(rc)) {
    printf("%s(%d)\n", sqlite3_errmsg(db), sqlite3_errcode(db));
  }

  if (check_name) {
    char check_property_value[PROP_VALUE_MAX];

    __system_property_get(check_name, check_property_value);

    printf("%s (%s %s) is not supported.\n", device, build_id, check_property_value);
  }
  else {
    printf("%s (%s) is not supported.\n", device, build_id);
  }

  sqlite3_finalize(st);
}

#undef __system_property_get

int
device_getprop(const char *name, char *value)
{
  if (value == NULL) {
    return 0;
  }

  *value = '\0';

  if (name == NULL || name[0] == '\0') {
    return 0;
  }

  __system_property_get(name, value);

  if (*value == '\0') {
    char buf[1024];
    size_t len;
    int pipefd[2];
    pid_t pid;
    int status;

    pipe(pipefd);

    pid = fork();
    if (pid == 0) {
      dup2(pipefd[1], 1);

      close(pipefd[0]);
      close(pipefd[1]);

      execlp("getprop", "getprop", name, NULL);
      exit(1);
    }

    close(pipefd[1]);

    len = read(pipefd[0], buf, sizeof buf);

    close(pipefd[0]);


    if (waitpid(pid, &status, 0) == pid
     && WIFEXITED(status)
     && WEXITSTATUS(status) == 0) {
      if (len) {
	char *token, *next;

	token = strtok_r(buf, "\r\n", &next);
	if (token && strlen(token) < PROP_VALUE_MAX) {
	  strcpy(value, token);
	}
      }
    }
  }

  return 0;
}

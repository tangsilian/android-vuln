all: device.db

device.db: db_init.sql
	rm -f device.db
	sqlite3 device.db < db_init.sql

clean:
	rm -f *.o
	rm -f make_db_init

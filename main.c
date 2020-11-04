// Copyright 2020 Dalimon Iarina

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./tema1.h"

int main(int argc, char *argv[]) {
	struct DoublyLinkedList *list;
	struct Node *cursor = NULL;
	struct Song_MP3 song;
	int q = 0, i = 0;
	char command[100], song_name[100], song_name_2[100], com[15], media_in[30],
		media_out[30], prefix[] = "./songs/";
	FILE *input, *output;

	list = malloc(sizeof(struct DoublyLinkedList));
	init_list(list);

	memset(command, 100, '0');
	memset(song_name, 100, '0');
	memset(com, 15, '0');
	memset(media_in, 30, '0');
	memset(media_out, 30, '0');
	memset(song_name_2, 100, '0');

	snprintf(media_out, strlen(argv[argc - 1]) + 1, "%s", argv[argc - 1]);
	snprintf(media_in, strlen(argv[argc - 2]) + 1, "%s", argv[argc - 2]);

	input = fopen(media_in, "rt");

	if (input == NULL) {
		return -1;
	}

	output = fopen(media_out, "wt");

	if (output == NULL) {
		return -1;
	}

	fscanf(input, "%d", &q);

	fseek(input, 1, SEEK_CUR);  // sare peste '\n'

	for (i = 0; i < q; i++) {
		fgets(command, 100, input);
		command[strlen(command) - 1] = '\0';

		read_files(command, com, song_name_2);

		snprintf(song_name, strlen(prefix) + 1, "%s", "./songs/");
		snprintf(song_name + strlen(song_name), strlen(song_name_2) + 1,
			 "%s", song_name_2);

		if (strcmp(command, com) != 0) {
			song = song_matadata(song_name, song_name_2);
		}
		go_command(com, song, list, &cursor, output);
		// if (cursor != NULL) {
		// 	printf("%s\n", cursor->data.name);
		// }
	}

	fclose(output);
	fclose(input);

	free_list(&list);
	return 0;
}

// Copyright 2020 Dalimon Iarina

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./tema1.h"

// fct de mai jos citeste comanda si numele melodiei daca este cazul
// ne folosim de faptul ca numele melodiei este despartit de comanda
// printr-un spatiu

void read_files(char command[100], char com[15], char song_name[100]) {
	int i = 0, k = 0, j = 0, n = 0;
	char copy[101];

	memset(copy, 101, '0');
	memset(com, 15, '0');
	memset(song_name, 100, '0');

	snprintf(copy, strlen(command) + 1, "%s", command);
	n = strlen(copy);

	for (i = 0; i < n; i++) {
		if (copy[i] == ' ') {
			k = i;
			break;
		}
	}
	if (k == 0) {
		snprintf(com, strlen(command) + 1, "%s", command);
		song_name[0] = '\0';
	} else {
		snprintf(com, k + 1, "%s", command);
		com[k] = '\0';
		for (i = k + 1; i < n; i++) {
			song_name[j] = copy[i];
			j++;
		}
		song_name[j] = '\0';
	}
}

void init_list(struct DoublyLinkedList *list) {
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
}

// functia de mai jos returneaza un pointer catre melodia data
// ca si parametru daca se afla in playlist; in caz contrat
// returneaza NULL
// in cadrul acestei functii se compara numele melodiei cu
// numele fiecarei melodii din playlist

struct Node *find_song(struct DoublyLinkedList *list, char curr[100]) {
    struct Node *copy;
    if (list == NULL || list->head == NULL) {
    	copy = NULL;
        return copy;
    }
    copy = list->head;
    if (list->size == 1) {
		if (strcmp((char *)(copy->data.name), curr) == 0) {
			return copy;
		}
    } else {
        while (copy->next != NULL) {
			if (strcmp((char *)(copy->data.name), curr) == 0) {
				return copy;
			} else {
            	copy = copy->next;
            }
        }
		if (strcmp((char *)(copy->data.name), curr) == 0) {
			return copy;
		}
    }
    copy = NULL;
    return copy;
}

// fct de mai jos adauga pe prima pozitie melodia data ca si parametru

void add_first_node(struct DoublyLinkedList *list, struct Song_MP3 data,
		struct Node **cursor) {
	struct Node *new_node;
	if (list == NULL) {
		return;
	}
	new_node = (struct Node*)malloc(sizeof(struct Node));
	if (new_node == NULL) {
		return;
	}

	snprintf(new_node->data.name, strlen(data.name) + 1, "%s", data.name);
	snprintf(new_node->data.title, strlen(data.title) + 1, "%s", data.title);
	snprintf(new_node->data.artist, strlen(data.artist) + 1, "%s", data.artist);
	snprintf(new_node->data.album, strlen(data.album) + 1, "%s", data.album);
	snprintf(new_node->data.year, strlen(data.year) + 1, "%s", data.year);

	if (list->size == 0) {
		*cursor = new_node;
		list->head = new_node;
		list->tail = new_node;
		list->head->prev = NULL;
		list->tail->next = NULL;
		list->size++;
		return;
	}
	new_node->next = list->head;
	list->head->prev = new_node;
	new_node->prev = NULL;
	list->head = new_node;
	list->size++;
	return;
}

// functia de mai jos adauga pe ultima pozitie melodia data ca si parametru

void add_last_node(struct DoublyLinkedList *list, struct  Song_MP3 data,
		struct Node **cursor) {
	struct Node *new_node;
	if (list == NULL) {
		return;
	}
	new_node = (struct Node *)malloc(sizeof(struct Node));
	if (new_node == NULL) {
		return;
	}
	snprintf(new_node->data.name, strlen(data.name) + 1, "%s", data.name);
	snprintf(new_node->data.title, strlen(data.title) + 1, "%s", data.title);
	snprintf(new_node->data.artist, strlen(data.artist) + 1, "%s", data.artist);
	snprintf(new_node->data.album, strlen(data.album) + 1, "%s", data.album);
	snprintf(new_node->data.year, strlen(data.year) + 1, "%s", data.year);
	if (list->size == 0) {
		*cursor = new_node;
		list->head = new_node;
		list->tail = new_node;
		list->head->prev = NULL;
		list->tail->next = NULL;
		list->size++;
		return;
	}
	list->tail->next = new_node;
	new_node->prev = list->tail;
	new_node->next = NULL;
	list->tail = new_node;
	list->size++;
	return;
}

// in urma apelarii fct de mai jos, este adaugata in playlist, dupa
// cursor, melodia data ca si parametru

void add_after_node(struct DoublyLinkedList *list, struct Song_MP3 data,
		struct Node **cursor) {
	struct Node *new_node;
	struct Node *cursor_nou = *cursor;
	if (list == NULL || cursor_nou == NULL || list->head == NULL) {
		return;
	}
	new_node = (struct Node *)malloc(sizeof(struct Node));
	if (new_node == NULL) {
		return;
	}
	snprintf(new_node->data.name, strlen(data.name) + 1, "%s", data.name);
	snprintf(new_node->data.title, strlen(data.title) + 1, "%s", data.title);
	snprintf(new_node->data.artist, strlen(data.artist) + 1, "%s", data.artist);
	snprintf(new_node->data.album, strlen(data.album) + 1, "%s", data.album);
	snprintf(new_node->data.year, strlen(data.year) + 1, "%s", data.year);
	if (cursor_nou == list->tail) {
		cursor_nou->next = new_node;
		new_node->prev = cursor_nou;
		new_node->next = NULL;
		list->tail = new_node;
		list->size++;
		*cursor = cursor_nou;
		return;
	}

	if (strcmp(cursor_nou->data.name, data.name) == 0) {
		free(new_node);
		return;
	}
	new_node->next = cursor_nou->next;
	cursor_nou->next->prev = new_node;
	cursor_nou->next = new_node;
	new_node->prev = cursor_nou;
	list->size++;
	*cursor = cursor_nou;
	return;
}

// functia de mai jos are scopul de a sterge melodia de pe prima pozitie

void del_first_node(struct DoublyLinkedList *list, struct Node **cursor,
		FILE *output) {
	struct Node *curr;
	struct Node *cursor_nou = *cursor;
	if (list == NULL || list->head == NULL) {
		fprintf(output, "Error: delete from empty playlist\n");
		return;
	}
	if (list->size == 1) {
		free(list->head);
		list->size--;
		list->head = NULL;
		cursor_nou = NULL;
		*cursor = cursor_nou;
		return;
	}
	curr = list->head;
	list->head = curr->next;
	list->head->prev = NULL;
	if (cursor_nou == curr) {
		cursor_nou = list->head;
	}
	free(curr);
	list->size--;
	*cursor = cursor_nou;
	return;
}

// functia de mai jos are scopul de a sterge melodia de pe ultima pozitie

void del_last_node(struct DoublyLinkedList *list, struct Node **cursor,
		FILE *output) {
	struct Node *curr;
	struct Node *cursor_nou = *cursor;
	if (list == NULL || list->head == NULL) {
		fprintf(output, "Error: delete from empty playlist\n");
		return;
	}
	if (list->size == 1) {
		free(list->head);
		list->size--;
		list->head = NULL;
		cursor_nou = NULL;
		*cursor = cursor_nou;
		return;
	}
	curr = list->tail;
	list->tail = curr->prev;
	list->tail->next = NULL;
	if (cursor_nou == curr) {
		cursor_nou = list->tail;
	}
	free(curr);
	list->size--;
	*cursor = cursor_nou;
	return;
}

// functia de mai jos are scopul de a sterge melodia spre care
// pointeaza cursorul

void del_curr_node(struct DoublyLinkedList *list, struct Node **cursor,
		FILE *output) {
	struct Node *curr;
	struct Node *cursor_nou = *cursor;
	if (list == NULL || cursor_nou == NULL || list->head == NULL) {
		fprintf(output, "Error: no track playing\n");
		return;
	}
	curr = cursor_nou;
	if (curr == list->head) {
		del_first_node(list, &cursor_nou, output);
		*cursor = cursor_nou;
		return;
	}
	if (curr == list->tail) {
		del_last_node(list, &cursor_nou, output);
		*cursor = cursor_nou;
		return;
	}
	cursor_nou = curr->next;
	*cursor = cursor_nou;
	curr->prev->next = curr->next;
	curr->next->prev = curr->prev;
	free(curr);
	list->size--;
	return;
}

// functia de mai jos are scopul de a sterge melodia data ca parametru

void del_song_node(struct DoublyLinkedList *list, struct Node **cursor,
		struct Node *curr, FILE *output) {
	struct Node *cursor_nou = *cursor;
	if (list == NULL || cursor_nou == NULL || list == NULL || list->head == NULL) {
		fprintf(output, "Error: no song found to delete\n");
		return;
	}
	if (curr == list->head) {
		del_first_node(list, &cursor_nou, output);
		*cursor = cursor_nou;
		return;
	}
	if (curr == list->tail) {
		del_last_node(list, &cursor_nou, output);
		*cursor = cursor_nou;
		return;
	}
	if (curr == cursor_nou) {
		cursor_nou = curr->next;
		*cursor = cursor_nou;
	}
	curr->prev->next = curr->next;
	curr->next->prev = curr->prev;
	free(curr);
	list->size--;
	return;
}

// cele 2 fct de mai jos modifica pozitia cursorului cu o pozitie
// mai la dreapta, respectiv stanga, daca este posibil

void move_next(struct DoublyLinkedList *list, struct Node **cursor,
		FILE *output) {
	struct Node *cursor_nou = *cursor;
	if (list == NULL || list->head == NULL || cursor_nou == NULL) {
		fprintf(output, "Error: no track playing\n");
		return;
	}
	if (cursor_nou == list->tail) {
		return;
	}
	cursor_nou = cursor_nou->next;
	*cursor = cursor_nou;
	return;
}

void move_prev(struct DoublyLinkedList *list, struct Node **cursor,
		FILE *output) {
	struct Node *cursor_nou = *cursor;
	if (list == NULL || list->head == NULL || cursor_nou == NULL) {
		fprintf(output, "Error: no track playing\n");
		return;
	}
	if (cursor_nou == list->head) {
		return;
	}
	cursor_nou = cursor_nou->prev;
	*cursor = cursor_nou;
	return;
}

// fct de mai jos afiseaza metadatele despre prima melodie din playlist

void show_first_node(struct DoublyLinkedList *list, FILE *output) {
	struct Node *curr;
	if(list == NULL || list->head == NULL) {
		fprintf(output, "Error: show empty playlist\n");
		return;
	}
	curr = list->head;
	fprintf(output, "Title: %s\n", curr->data.title);
	fprintf(output, "Artist: %s\n", curr->data.artist);
	fprintf(output, "Album: %s\n", curr->data.album);
	fprintf(output, "Year: %s\n", curr->data.year);
	return;
}

// fct de mai jos afiseaza metadatele despre ultima melodie din playlist

void show_last_node(struct DoublyLinkedList *list, FILE *output) {
	struct Node *curr;
	if(list == NULL || list->head == NULL) {
		fprintf(output, "Error: show empty playlist\n");
		return;
	}
	curr = list->tail;
	fprintf(output, "Title: %s\n", curr->data.title);
	fprintf(output, "Artist: %s\n", curr->data.artist);
	fprintf(output, "Album: %s\n", curr->data.album);
	fprintf(output, "Year: %s\n", curr->data.year);
	return;
}

// fct de mai jos afiseaza metadatele despre melodia spre care
// pointeaza cursorul

void show_curr_node(struct DoublyLinkedList *list, struct Node *cursor,
		FILE *output) {
	struct Node *curr;
	if(list == NULL || list->head == NULL || cursor == NULL) {
		fprintf(output, "Error: show empty playlist\n");
		return;
	}
	curr = cursor;
	fprintf(output, "Title: %s\n", curr->data.title);
	fprintf(output, "Artist: %s\n", curr->data.artist);
	fprintf(output, "Album: %s\n", curr->data.album);
	fprintf(output, "Year: %s\n", curr->data.year);
	return;
}

// fct de mai jos afiseaza titlul melodiilor din playlist

void show_playlist_list(struct DoublyLinkedList *list, FILE *output) {
    struct Node *curr;
    if (list == NULL || list->head == NULL) {
    	fprintf(output, "[]\n");
        return;
    }
    curr = list->head;
    if (list-> size == 1) {
		fprintf(output, "[%s]\n", curr->data.title);
    } else {
    	fprintf(output, "[");
        while (curr->next != NULL) {
			fprintf(output, "%s; ", curr->data.title);
            curr = curr->next;
        }
		fprintf(output, "%s]\n", curr->data.title);
    }
}

// fct de mai jos este folosita pentru a elibera memoria

void free_list(struct DoublyLinkedList **pp_list) {
    struct DoublyLinkedList *list = *pp_list;
    struct Node *curr, *prev;
    if (list == NULL) {
        return;
    }
    if (list->head == NULL) {
    	free(list->head);
    	free(list);
    	*pp_list = NULL;
    	return;
    }
    curr = list->head;
    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
        free(prev);
    }
    free(curr);
    free(list);
    *pp_list = NULL;
}

// in cadrul functiei urmatoare, metadatele melodiei date ca si parametru
// sunt stocata intr-o variabil de tipul struct Song_MP3; fct returneaza
// aceasta variabila

struct Song_MP3 song_matadata(char song_name[100], char song_name_2[100]) {
	FILE *song_file;
	struct Song_MP3 song;

	song_file = fopen(song_name, "rb");

	if (song_file == NULL) {
		exit(-1);
	}

	snprintf(song.name, strlen(song_name_2) + 1, "%s", song_name_2);
	song.name[strlen(song_name_2) + 1] = '\0';
	fseek(song_file, -94, SEEK_END);
	fgets(song.title, 31, song_file);
	fseek(song_file, -64, SEEK_END);
	fgets(song.artist, 31, song_file);
	fseek(song_file, -34, SEEK_END);
	fgets(song.album, 31, song_file);
	fseek(song_file, -4, SEEK_END);
	fgets(song.year, 5, song_file);
	song.year[4] = '\0';

	fclose(song_file);

	return song;
}

void go_command(char com[15], struct Song_MP3 song,
		struct DoublyLinkedList *list, struct Node **cursor, FILE *output) {
	struct Node *curr;
	struct Node *cursor_nou = *cursor;
	if (strcmp(com, "ADD_FIRST") == 0) {
		curr = find_song(list, song.name);
		if (curr == NULL) {
			add_first_node(list, song, &cursor_nou);
			*cursor = cursor_nou;
			return;
		} else {
			del_song_node(list, &cursor_nou, curr, output);
			*cursor = cursor_nou;
			add_first_node(list, song, &cursor_nou);
			*cursor = cursor_nou;
			return;
		}
	}
	if (strcmp(com, "ADD_LAST") == 0) {
		curr = find_song(list, song.name);
		if (curr == NULL) {
			add_last_node(list, song, &cursor_nou);
			*cursor = cursor_nou;
			return;
		} else {
			del_song_node(list, &cursor_nou, curr, output);
			*cursor = cursor_nou;
			add_last_node(list, song, &cursor_nou);
			*cursor = cursor_nou;
			return;
		}
	}
	if (strcmp(com, "ADD_AFTER") == 0) {
		curr = find_song(list, song.name);
		if (cursor_nou == curr) {
			return;
		}
		if (curr == NULL) {
			add_after_node(list, song, &cursor_nou);
			*cursor = cursor_nou;
			return;
		} else {
			del_song_node(list, &cursor_nou, curr, output);
			*cursor = cursor_nou;
			add_after_node(list, song, &cursor_nou);
			*cursor = cursor_nou;
			return;
		}
	}
	if (strcmp(com, "DEL_FIRST") == 0) {
		del_first_node(list, &cursor_nou, output);
		*cursor = cursor_nou;
		return;
	}
	if (strcmp(com, "DEL_LAST") == 0) {
		del_last_node(list, &cursor_nou, output);
		*cursor = cursor_nou;
		return;
	}
	if (strcmp(com, "DEL_CURR") == 0) {
		del_curr_node(list, &cursor_nou, output);
		*cursor = cursor_nou;
		return;
	}
	if (strcmp(com, "DEL_SONG") == 0) {
		curr = find_song(list, song.name);
		if (curr == NULL) {
			fprintf(output, "Error: no song found to delete\n");
			return;
		}
		del_song_node(list, &cursor_nou, curr, output);
		*cursor = cursor_nou;
		return;
	}
	if (strcmp(com, "MOVE_NEXT") == 0) {
		move_next(list, &cursor_nou, output);
		*cursor = cursor_nou;
		return;
	}
	if (strcmp(com, "MOVE_PREV") == 0) {
		move_prev(list, &cursor_nou, output);
		*cursor = cursor_nou;
		return;
	}
	if (strcmp(com, "SHOW_FIRST") == 0) {
		show_first_node(list, output);
		return;
	}
	if (strcmp(com, "SHOW_LAST") == 0) {
		show_last_node(list, output);
		return;
	}
	if (strcmp(com, "SHOW_CURR") == 0) {
		show_curr_node(list, *cursor, output);
		return;
	}
	if (strcmp(com, "SHOW_PLAYLIST") == 0) {
		show_playlist_list(list, output);
		return;
	}
}

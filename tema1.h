// Copyright 2020 Dalimon Iarina

#ifndef TEMA1_H__
#define TEMA1_H__
#include <stdio.h>

// in structura de mai jos pastrez metadatele melodiilor

struct Song_MP3 {
	char name[100];
	char title[31];
	char artist[31];
	char album[31];
	char year[5];
};

struct Node {
	struct Song_MP3 data;
	struct Node *next;
	struct Node *prev;
};

struct DoublyLinkedList {
	struct Node *head;
	struct Node *tail;
	int size;
};

void read_files(char command[100], char com[15], char song_name[100]);

void init_list(struct DoublyLinkedList *list);

struct Node *find_song(struct DoublyLinkedList *list, char curr[100]);

void add_first_node(struct DoublyLinkedList *list,
	struct Song_MP3 data, struct Node **cursor);

void add_last_node(struct DoublyLinkedList *list, struct  Song_MP3 data,
	struct Node **cursor);

void add_after_node(struct DoublyLinkedList *list, struct Song_MP3 data,
	struct Node **cursor);

void del_first_node(struct DoublyLinkedList *list, struct Node **cursor,
	FILE *output);

void del_last_node(struct DoublyLinkedList *list, struct Node **cursor,
	FILE *output);

void del_curr_node(struct DoublyLinkedList *list, struct Node **cursor,
	FILE *output);

void del_song_node(struct DoublyLinkedList *list, struct Node **cursor,
	struct Node *curr, FILE *output);

void move_next(struct DoublyLinkedList *list, struct Node **cursor,
	FILE *output);

void move_prev(struct DoublyLinkedList *list, struct Node **cursor,
	FILE *output);

void show_first_node(struct DoublyLinkedList *list, FILE *output);

void show_last_node(struct DoublyLinkedList *list, FILE *output);

void show_curr_node(struct DoublyLinkedList *list, struct Node *cursor,
	FILE *output);

void show_playlist_list(struct DoublyLinkedList *list, FILE *output);

void free_list(struct DoublyLinkedList **pp_list);

struct Song_MP3 song_matadata(char song_name[100], char song_name_2[100]);

void go_command(char com[15], struct Song_MP3 song,
	struct DoublyLinkedList *list, struct Node **cursor, FILE *output);

#endif  // TEMA1_H_

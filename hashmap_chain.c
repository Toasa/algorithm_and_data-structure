#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CAPACITY 1024

typedef struct HashEntry HashEntry;
struct HashEntry {
    char *key;
    void *val;
    int keylen;
    HashEntry *next;
};

typedef struct HashMap HashMap;
struct HashMap {
    HashEntry *buckets;
    int used;
};

HashEntry *new_entry(char *key, int keylen);
HashMap *new_map();
static uint64_t fnv_hash(char *s, int len);
bool match(char *key, int keylen, HashEntry *ent);
void put(HashMap *hm, char *key, void *val);
void put2(HashMap *hm, char *key, int keylen, void *val);
HashEntry *get_or_insert(HashMap *hm, char *key, int keylen);
HashEntry *get(HashMap *hm, char *key);
HashEntry *get2(HashMap *hm, char *key, int keylen);

HashEntry *new_entry(char *key, int keylen) {
    HashEntry *ent = calloc(1, sizeof(HashEntry));
    ent->key = key;
    ent->keylen = keylen;
    return ent;
}

HashMap *new_map() {
    HashMap *map = calloc(1, sizeof(HashMap));
    map->buckets = calloc(CAPACITY, sizeof(HashEntry));
    return map;
}

static uint64_t fnv_hash(char *s, int len) {
    uint64_t hash = 0xcbf29ce484222325;
    for (int i = 0; i < len; i++) {
        hash *= 0x100000001b3;
        hash ^= s[i];
    }
    return hash;
}

bool match(char *key, int keylen, HashEntry *ent) {
    if (keylen != ent->keylen) {
        return false;
    }
    return !strncmp(key, ent->key, keylen);
}

void put(HashMap *hm, char *key, void *val) {
    put2(hm, key, strlen(key), val);
}

void put2(HashMap *hm, char *key, int keylen, void *val) {
    HashEntry *ent = get_or_insert(hm, key, keylen);
    ent->val = val;
}

HashEntry *get_or_insert(HashMap *hm, char *key, int keylen) {
    uint64_t hash = fnv_hash(key, keylen);
    HashEntry *ent = &hm->buckets[hash % CAPACITY];
    for (;;) { 
        if (match(key, keylen, ent)) {
            return ent;
        }
        if (ent->key == NULL) {
            HashEntry *next = new_entry(key, keylen);
            ent->next = next;
            ent->key = key;
            ent->keylen = keylen;
            return ent;
        }
        ent = ent->next;
    }
}

HashEntry *get(HashMap *hm, char *key) {
    return get2(hm, key, strlen(key));
}

HashEntry *get2(HashMap *hm, char *key, int keylen) {
    uint64_t hash = fnv_hash(key, keylen);
    HashEntry *ent = &hm->buckets[hash % CAPACITY];
    for (;;) {
        if (match(key, keylen, ent)) {
            return ent;
        }
        if (ent->next == NULL) {
            return NULL;
        }
        ent = ent->next;
    }
}

typedef struct Song {
    char *name;
    char *artist;
    int len;
} Song;

Song *new_song(char *name, char *artist, int len) {
    Song *s = calloc(1, sizeof(struct Song));
    s->name = name;
    s->artist = artist;
    s->len = len;
    return s;
}

void print_song(Song *s) {
    printf("name: %s\n", s->name);
    printf("artist: %s\n", s->artist);
    printf("len: %d\n", s->len);
}

int main() {
    HashMap *map = new_map();

    put(
        map,
        "blue",
        new_song("BLUE", "Utada Hikaru", 180)
    );
    put(
        map,
        "vanilla",
        new_song("Vanila", "Gackt", 230)
    );

    print_song(get(map, "blue")->val);
    print_song(get(map, "vanilla")->val);

    return 0;
}

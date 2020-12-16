#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INIT_SIZE 16

// Rehash if the usage exceeds 70%.
#define HIGH_WATERMARK 70

// We'll keep the usage below 50% after rehashing.
#define LOW_WATERMARK 50

typedef struct HashEntry HashEntry;
struct HashEntry {
    char *key;
    void *val;
    int keylen;
};

typedef struct HashMap HashMap;
struct HashMap {
    HashEntry *buckets;
    int cap;
    int used;
};

static HashMap *init();
static uint64_t fnv_hash(char *s, int len);
static void rehash(HashMap *hm);
static HashEntry *get_or_insert_entry(HashMap *hm, char *key, int keylen);
static void put(HashMap *hm, char *key, void *val);
static void put2(HashMap *hm, char *key, int keylen, void *val);
static HashEntry *get(HashMap *hm, char *key);
static HashEntry *get2(HashMap *hm, char *key, int keylen);
static bool match(HashEntry *ent, char *key, int keylen);

static HashMap *init() {
    HashMap *hm = calloc(1, sizeof(HashMap));
    hm->cap = INIT_SIZE;
    hm->buckets = calloc(INIT_SIZE, sizeof(HashEntry));
    return hm;
}

// ref. https://en.wikipedia.org/wiki/Fowler-Noll-Vo_hash_function
static uint64_t fnv_hash(char *s, int len) {
    uint64_t hash = 0xcbf29ce484222325;
    for (int i = 0; i < len; i++) {
        hash *= 0x100000001b3;
        hash ^= s[i];
    }
    return hash;
}

static void rehash(HashMap *hm) {
    // Compute the size of new hash map;
    int nkeys = 0;
    for (int i = 0; i < hm->cap; i++) {
        HashEntry *ent = &hm->buckets[i];
        if (ent->key != NULL) {
            nkeys++;
        }
    }

    int cap = hm->cap;
    while ((nkeys * 100) / cap >= LOW_WATERMARK) {
        cap *= 2;
    }

    HashMap *hm2 = calloc(1, sizeof(HashMap));
    hm2->cap = cap;
    hm2->buckets = calloc(cap, sizeof(HashEntry));
    for (int i = 0; i < hm->cap; i++) {
        HashEntry *ent = &hm->buckets[i];
        if (ent->key != NULL) {
            put(hm2, ent->key, ent->val);
        }
    }

    *hm = *hm2;
}

static HashEntry *get_or_insert_entry(HashMap *hm, char *key, int keylen) {
    if ((hm->used * 100) / hm->cap >= HIGH_WATERMARK) {
        rehash(hm);
    }

    uint64_t hash = fnv_hash(key, keylen);
    for (int i = 0; i < hm->cap; i++)  {
        HashEntry *ent = &hm->buckets[(i + hash) % hm->cap];
        if (match(ent, key, keylen)) {
            return ent;
        }

        if (ent->key == NULL) {
            ent->key = key;
            ent->keylen = keylen;
            hm->used++;
            return ent;
        }
    }
}

static void put(HashMap *hm, char *key, void *val) {
    put2(hm, key, strlen(key), val);
}

static void put2(HashMap *hm, char *key, int keylen, void *val) {
    HashEntry *ent = get_or_insert_entry(hm, key, keylen);
    ent->val = val;
}

static HashEntry *get(HashMap *hm, char *key) {
    return get2(hm, key, strlen(key));
}

static HashEntry *get2(HashMap *hm, char *key, int keylen) {
    uint64_t hash = fnv_hash(key, keylen);
    for (int i = 0; i < hm->cap; i++)  {
        HashEntry *ent = &hm->buckets[(i + hash) % hm->cap];
        if (match(ent, key, keylen)) {
            return ent;
        }
        if (ent->key == NULL) {
            return NULL;
        }
    }
}

static bool match(HashEntry *ent, char *key, int keylen) {
    if (ent->key == NULL || ent->keylen != keylen) {
        return false;
    }
    return !strncmp(ent->key, key, keylen);
}

typedef struct Person Person;
struct Person {
    char *name;
    int age;
};

Person *new_person(char *name, int age) {
    Person *p = calloc(1, sizeof(Person));
    p->name = name;
    p->age = age;
    return p;
}

void print_person(Person *p) {
    printf("name: %s\n", p->name);
    printf("age: %d\n", p->age);
}

int main() {
    HashMap *hm = init();
    Person *p1 = new_person("atsushi", 28);
    Person *p2 = new_person("takashi", 26);
    put(hm, "atsu", p1);
    put(hm, "taka", p2);

    HashEntry *e1 = get(hm, "atsu");
    HashEntry *e2 = get(hm, "taka");
    print_person(e1->val);
    print_person(e2->val);

    HashEntry *e3 = get(hm, "nothing");
    printf("%d\n", e3 == NULL);

    return 0;
}

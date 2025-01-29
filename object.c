#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "memory.h"
#include "object.h"
#include "value.h"
#include "vm.h"
#include "../surajutil.h"

// Define macro to skip manual casting of allocateObject
#define ALLOCATE_OBJ(type, objectType) \
    (type*)allocateObject(sizeof(type), objectType)

static Obj* allocateObject(size_t size, ObjType type) {
    Obj* object = (Obj*)reallocate(NULL, 0, size);
    object->type = type;

    object->next = vm.objects;
    vm.objects = object;
    return object;
}

ObjString* allocateString(char* chars, int length,
                          uint32_t hash) {
    // Given a char array, allocate a string object and return a pointer to it
    ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
    string->length = length;
    string->chars = chars;
    string->hash = hash;
    tableSet(&vm.strings, string, NIL_VAL); // intern as chars -> NIL pair
    return string;
}

static uint32_t hashString(const char* key, int length) {
    // FNV-1a hash algorithm
    uint32_t hash = 2166136261u;
    for (int i = 0; i < length; i++) {
        hash ^= key[i];
        hash *= 16777619;
    }
    return hash;
}

ObjString* takeString(char* chars, int length) {
    uint32_t hash = hashString(chars, length);
    ObjString* interned = tableFindString(&vm.strings, chars, length, hash);
    if (interned != NULL) { // If interned, free input string; return intern
        FREE_ARRAY(char, chars, length + 1);
        return interned;
    }
    return allocateString(chars, length, hash);
}

ObjString* copyString(const char* chars, int length) {
    // create a copy of the string on the heap
    uint32_t hash = hashString(chars, length);
    
    // If the string is already interned, return the interned version
    ObjString* interned = tableFindString(&vm.strings, chars, length, hash);
    if (interned != NULL) return interned;

    char* new = substr(chars, 0, length);

    #ifdef DEBUG_TRACE_EXECUTION // track interns for debugging
        printf("in copyString:\n");
        if (interned == NULL) printf("\tnot found; new intern=<%s>; \n", new);
        else printf("\tintern from find: %d\n", interned->length);
        free(new);
    #endif

    char* heapChars = ALLOCATE(char, length + 1);
    memcpy(heapChars, chars, length);
    heapChars[length] = '\0';
    return allocateString(heapChars, length, hash);
}

void printObject(Value value) {
    switch (OBJ_TYPE(value)) {
        case OBJ_STRING:
            printf("%s", AS_CSTRING(value));
            break;
    }
}
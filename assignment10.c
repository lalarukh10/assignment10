
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET_SIZE 26
// trie node struct
struct Trie {
   int count;
   struct Trie *children[ALPHABET_SIZE];
};
// initializes a new trie node
struct Trie *newNode(void) {
   struct Trie *node = (struct Trie *) malloc(sizeof(struct Trie));
   node->count = 0;
   for (int i = 0; i < ALPHABET_SIZE; i++) {
       node->children[i] = NULL;
   }
   return node;
}
// inserts a word into the trie
void insert(struct Trie **ppTrie, char *word) {
   if (word == NULL || strlen(word) == 0) {
       return;
   }
   struct Trie *curr = *ppTrie;
   if (curr == NULL) {
       curr = newNode();
       *ppTrie = curr;
   }
   for (int i = 0; i < strlen(word); i++) {
       int index = word[i] - 'a';
       if (curr->children[index] == NULL) {
           curr->children[index] = newNode();
       }
       curr = curr->children[index];
   }
   curr->count++;
}
// finds the number of occurrences of a word in the trie
int numberOfOccurances(struct Trie *pTrie, char *word) {
   if (word == NULL || strlen(word) == 0 || pTrie == NULL) {
       return 0;
   }
   struct Trie *curr = pTrie;
   for (int i = 0; i < strlen(word); i++) {
       int index = word[i] - 'a';
       if (curr->children[index] == NULL) {
           return 0;
       }
       curr = curr->children[index];
   }
   return curr->count;
}
// deallocates the trie
struct Trie *deallocateTrie(struct Trie *pTrie) {
   if (pTrie == NULL) {
       return NULL;
   }
   for (int i = 0; i < ALPHABET_SIZE; i++) {
       if (pTrie->children[i] != NULL) {
           deallocateTrie(pTrie->children[i]);
       }
   }
   free(pTrie);
   return NULL;
}
int main(void) {
   struct Trie *trie = NULL;
   char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
   // insert each word into the trie
   int numWords = sizeof(pWords) / sizeof(pWords[0]);
   for (int i = 0; i < numWords; i++) {
       insert(&trie, pWords[i]);
   }
   // find the number of occurrences of each word in the trie
   for (int i = 0; i < numWords; i++) {
       printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
   }
   // deallocate the trie
   trie = deallocateTrie(trie);
   if (trie != NULL) {
       printf("There is an error in this program\n");
   }
   return 0;
}
 

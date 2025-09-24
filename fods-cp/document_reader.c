#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

// Maximum sizes for various elements
#define MAX_WORD_LENGTH 100
#define MAX_TOKENS 10000
#define MAX_STOPWORDS 1000
#define MAX_KGRAMS 5000
#define MAX_KGRAM_LENGTH 500
#define MAX_REFERENCE_PAPERS 10
#define HASH_TABLE_SIZE 10007  // Prime number for better distribution

// Structure to store tokens
typedef struct {
    char** tokens;
    int count;
} TokenList; 

// Structure for k-grams
typedef struct {
    char** kgrams;
    int count;
    int k_value;
} KGramList;

// Hash table node for storing k-grams
typedef struct HashNode {
    char* kgram;
    int count;
    struct HashNode* next;
} HashNode;

// Hash table structure
typedef struct {
    HashNode** table;
    int size;
    int count;
} HashTable;

// DocumentReader class equivalent in C
typedef struct {
    char* filename;
    TokenList token_list;
    KGramList kgram_list;
    HashTable* kgram_hash;
    char* stopwords[MAX_STOPWORDS];
    int stopwords_count;
} DocumentReader;

// PlagiarismChecker class equivalent in C
typedef struct {
    DocumentReader* target_doc;
    DocumentReader* reference_docs[MAX_REFERENCE_PAPERS];
    int reference_count;
    float similarity_scores[MAX_REFERENCE_PAPERS];
    float overall_similarity;
} PlagiarismChecker;

// Function prototypes - Member 1
DocumentReader* create_document_reader();
void load_stopwords(DocumentReader* reader, const char* stopwords_file);
void read_document(DocumentReader* reader, const char* filename);
void preprocess_text(DocumentReader* reader);
void to_lowercase(char* str);
void remove_punctuation_numbers(char* str);
bool is_stopword(DocumentReader* reader, const char* word);
void tokenize_text(DocumentReader* reader, const char* text);
void free_document_reader(DocumentReader* reader);
void print_tokens(DocumentReader* reader);
void export_tokens(DocumentReader* reader, const char* filename);

// Function prototypes - Member 2
void generate_kgrams(DocumentReader* reader, int k);
HashTable* create_hash_table(int size);
unsigned int hash_function(const char* str, int table_size);
void hash_table_insert(HashTable* ht, const char* kgram);
bool hash_table_contains(HashTable* ht, const char* kgram);
void print_kgrams(DocumentReader* reader);
void print_hash_table_stats(HashTable* ht);
void free_hash_table(HashTable* ht);
void export_kgrams(DocumentReader* reader, const char* filename);

// Function prototypes - Member 3
PlagiarismChecker* create_plagiarism_checker();
void add_target_document(PlagiarismChecker* checker, DocumentReader* target);
void add_reference_document(PlagiarismChecker* checker, DocumentReader* reference);
float calculate_jaccard_similarity(HashTable* set1, HashTable* set2);
float calculate_cosine_similarity(HashTable* set1, HashTable* set2);
int hash_table_intersection_count(HashTable* set1, HashTable* set2);
int hash_table_union_count(HashTable* set1, HashTable* set2);
void compare_documents(PlagiarismChecker* checker, int k_value);
void print_comparison_results(PlagiarismChecker* checker);
void export_results(PlagiarismChecker* checker, const char* filename);
void free_plagiarism_checker(PlagiarismChecker* checker);

int main() {
    printf("=== PLAGIARISM DETECTION SYSTEM ===\n\n");
    
    // Create document readers for all papers
    DocumentReader* target_reader = create_document_reader();
    DocumentReader* ref_reader1 = create_document_reader();
    DocumentReader* ref_reader2 = create_document_reader();
    DocumentReader* ref_reader3 = create_document_reader();
    DocumentReader* ref_reader4 = create_document_reader();
    
    // Load stopwords
    load_stopwords(target_reader, "stopwords.txt");
    load_stopwords(ref_reader1, "stopwords.txt");
    load_stopwords(ref_reader2, "stopwords.txt");
    load_stopwords(ref_reader3, "stopwords.txt");
    load_stopwords(ref_reader4, "stopwords.txt");
    
    // Read and preprocess target document
    printf("1. PROCESSING TARGET DOCUMENT:\n");
    read_document(target_reader, "target_paper.txt");
    preprocess_text(target_reader);
    generate_kgrams(target_reader, 3);
    printf("Target document processed: %d tokens, %d k-grams\n\n", 
           target_reader->token_list.count, target_reader->kgram_list.count);
    
    // Read and preprocess reference documents
    printf("2. PROCESSING REFERENCE DOCUMENTS:\n");
    
    printf("Reference 1: ");
    read_document(ref_reader1, "research_paper1.txt");
    preprocess_text(ref_reader1);
    generate_kgrams(ref_reader1, 3);
    printf("Paper 1: %d tokens, %d k-grams\n", 
           ref_reader1->token_list.count, ref_reader1->kgram_list.count);
    
    printf("Reference 2: ");
    read_document(ref_reader2, "research_paper2.txt");
    preprocess_text(ref_reader2);
    generate_kgrams(ref_reader2, 3);
    printf("Paper 2: %d tokens, %d k-grams\n", 
           ref_reader2->token_list.count, ref_reader2->kgram_list.count);
    
    printf("Reference 3: ");
    read_document(ref_reader3, "research_paper3.txt");
    preprocess_text(ref_reader3);
    generate_kgrams(ref_reader3, 3);
    printf("Paper 3: %d tokens, %d k-grams\n", 
           ref_reader3->token_list.count, ref_reader3->kgram_list.count);
    
    printf("Reference 4: ");
    read_document(ref_reader4, "research_paper4.txt");
    preprocess_text(ref_reader4);
    generate_kgrams(ref_reader4, 3);
    printf("Paper 4: %d tokens, %d k-grams\n\n", 
           ref_reader4->token_list.count, ref_reader4->kgram_list.count);
    
    // MEMBER 3: Create plagiarism checker and perform comparison
    printf("3. PLAGIARISM ANALYSIS:\n");
    PlagiarismChecker* checker = create_plagiarism_checker();
    
    // Add documents to checker
    add_target_document(checker, target_reader);
    add_reference_document(checker, ref_reader1);
    add_reference_document(checker, ref_reader2);
    add_reference_document(checker, ref_reader3);
    add_reference_document(checker, ref_reader4);
    
    // Perform comparison with k=3 (3-word sequences)
    compare_documents(checker, 3);
    
    // Display results
    print_comparison_results(checker);
    
    // Export results
    export_results(checker, "plagiarism_report.txt");
    
    // Clean up
    free_plagiarism_checker(checker);
    free_document_reader(target_reader);
    free_document_reader(ref_reader1);
    free_document_reader(ref_reader2);
    free_document_reader(ref_reader3);
    free_document_reader(ref_reader4);
    
    return 0;
}

// ==================== MEMBER 1 FUNCTIONS (EXISTING) ====================

// Create a new DocumentReader instance
DocumentReader* create_document_reader() {
    DocumentReader* reader = (DocumentReader*)malloc(sizeof(DocumentReader));
    if (reader == NULL) {
        fprintf(stderr, "Memory allocation failed for DocumentReader\n");
        exit(EXIT_FAILURE);
    }
    
    reader->filename = NULL;
    reader->token_list.tokens = NULL;
    reader->token_list.count = 0;
    reader->kgram_list.kgrams = NULL;
    reader->kgram_list.count = 0;
    reader->kgram_list.k_value = 0;
    reader->kgram_hash = NULL;
    reader->stopwords_count = 0;
    
    return reader;
}

// Load stopwords from file into hash set (array implementation)
void load_stopwords(DocumentReader* reader, const char* stopwords_file) {
    FILE* file = fopen(stopwords_file, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open stopwords file %s\n", stopwords_file);
        return;
    }
    
    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) != EOF && reader->stopwords_count < MAX_STOPWORDS) {
        // Convert to lowercase
        to_lowercase(word);
        
        // Allocate memory for the stopword and add to array
        reader->stopwords[reader->stopwords_count] = strdup(word);
        reader->stopwords_count++;
    }
    
    fclose(file);
    printf("Loaded %d stopwords\n", reader->stopwords_count);
}

// Read document from file
void read_document(DocumentReader* reader, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return;
    }
    
    // Free previous filename if exists
    if (reader->filename != NULL) {
        free(reader->filename);
    }
    
    // Store filename
    reader->filename = strdup(filename);
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Allocate memory for file content
    char* content = (char*)malloc(file_size + 1);
    if (content == NULL) {
        fprintf(stderr, "Memory allocation failed for file content\n");
        fclose(file);
        return;
    }
    
    // Read file content
    fread(content, 1, file_size, file);
    content[file_size] = '\0';
    
    fclose(file);
    
    // Tokenize the text
    tokenize_text(reader, content);
    
    free(content);
    printf("Read %d words from %s\n", reader->token_list.count, filename);
}

// Preprocess text: lowercase, remove punctuation/numbers, remove stopwords
void preprocess_text(DocumentReader* reader) {
    int write_index = 0;
    
    for (int i = 0; i < reader->token_list.count; i++) {
        char* token = reader->token_list.tokens[i];
        
        // Convert to lowercase
        to_lowercase(token);
        
        // Remove punctuation and numbers
        remove_punctuation_numbers(token);
        
        // Check if token is empty after processing
        if (strlen(token) == 0) {
            free(token);
            continue;
        }
        
        // Remove stopwords
        if (is_stopword(reader, token)) {
            free(token);
            continue;
        }
        
        // Keep the token
        reader->token_list.tokens[write_index] = token;
        write_index++;
    }
    
    // Update token count
    reader->token_list.count = write_index;
    printf("After preprocessing: %d tokens remaining\n", write_index);
}

// Convert string to lowercase
void to_lowercase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Remove punctuation and numbers from string
void remove_punctuation_numbers(char* str) {
    int read_index = 0, write_index = 0;
    
    while (str[read_index]) {
        if (isalpha(str[read_index]) || str[read_index] == '\'') {
            str[write_index] = str[read_index];
            write_index++;
        }
        read_index++;
    }
    
    str[write_index] = '\0';
}

// Check if a word is a stopword (using array as simple hash set)
bool is_stopword(DocumentReader* reader, const char* word) {
    for (int i = 0; i < reader->stopwords_count; i++) {
        if (strcmp(reader->stopwords[i], word) == 0) {
            return true;
        }
    }
    return false;
}

// Tokenize text into words
void tokenize_text(DocumentReader* reader, const char* text) {
    // Free previous tokens if any
    for (int i = 0; i < reader->token_list.count; i++) {
        free(reader->token_list.tokens[i]);
    }
    free(reader->token_list.tokens);
    
    // Allocate memory for tokens
    reader->token_list.tokens = (char**)malloc(MAX_TOKENS * sizeof(char*));
    if (reader->token_list.tokens == NULL) {
        fprintf(stderr, "Memory allocation failed for tokens\n");
        exit(EXIT_FAILURE);
    }
    
    reader->token_list.count = 0;
    
    // Copy the text for tokenization (strtok modifies the original)
    char* text_copy = strdup(text);
    if (text_copy == NULL) {
        fprintf(stderr, "Memory allocation failed for text copy\n");
        return;
    }
    
    // Tokenize using whitespace as delimiter
    char* token = strtok(text_copy, " \t\n\r");
    while (token != NULL && reader->token_list.count < MAX_TOKENS) {
        reader->token_list.tokens[reader->token_list.count] = strdup(token);
        reader->token_list.count++;
        token = strtok(NULL, " \t\n\r");
    }
    
    free(text_copy);
}

// Print all tokens (for testing purposes)
void print_tokens(DocumentReader* reader) {
    for (int i = 0; i < reader->token_list.count; i++) {
        printf("%s ", reader->token_list.tokens[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n");
}

// Export tokens to file for other team members
void export_tokens(DocumentReader* reader, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not create file %s\n", filename);
        return;
    }
    
    for (int i = 0; i < reader->token_list.count; i++) {
        fprintf(file, "%s\n", reader->token_list.tokens[i]);
    }
    
    fclose(file);
    printf("Tokens exported to %s\n", filename);
}

// ==================== MEMBER 2 FUNCTIONS (EXISTING) ====================

// Generate k-grams using sliding window technique
void generate_kgrams(DocumentReader* reader, int k) {
    if (k <= 0 || k > reader->token_list.count) {
        fprintf(stderr, "Error: Invalid k value %d for token count %d\n", 
                k, reader->token_list.count);
        return;
    }
    
    // Free previous k-grams if any
    for (int i = 0; i < reader->kgram_list.count; i++) {
        free(reader->kgram_list.kgrams[i]);
    }
    free(reader->kgram_list.kgrams);
    
    if (reader->kgram_hash != NULL) {
        free_hash_table(reader->kgram_hash);
    }
    
    // Calculate number of k-grams
    int num_kgrams = reader->token_list.count - k + 1;
    if (num_kgrams <= 0) {
        reader->kgram_list.count = 0;
        return;
    }
    
    // Allocate memory for k-grams
    reader->kgram_list.kgrams = (char**)malloc(num_kgrams * sizeof(char*));
    if (reader->kgram_list.kgrams == NULL) {
        fprintf(stderr, "Memory allocation failed for k-grams\n");
        return;
    }
    
    reader->kgram_list.count = 0;
    reader->kgram_list.k_value = k;
    
    // Create hash table for efficient storage
    reader->kgram_hash = create_hash_table(HASH_TABLE_SIZE);
    
    // Generate k-grams using sliding window
    for (int i = 0; i <= reader->token_list.count - k; i++) {
        // Calculate required length for k-gram string
        int total_length = 0;
        for (int j = 0; j < k; j++) {
            total_length += strlen(reader->token_list.tokens[i + j]) + 1; // +1 for space
        }
        
        // Allocate memory for k-gram
        char* kgram = (char*)malloc(total_length);
        if (kgram == NULL) {
            fprintf(stderr, "Memory allocation failed for k-gram\n");
            continue;
        }
        
        // Build k-gram string
        kgram[0] = '\0'; // Start with empty string
        for (int j = 0; j < k; j++) {
            strcat(kgram, reader->token_list.tokens[i + j]);
            if (j < k - 1) {
                strcat(kgram, " ");
            }
        }
        
        // Store k-gram in array
        reader->kgram_list.kgrams[reader->kgram_list.count] = kgram;
        reader->kgram_list.count++;
        
        // Store k-gram in hash table (manages duplicates)
        hash_table_insert(reader->kgram_hash, kgram);
    }
    
    printf("Generated %d k-grams with k=%d\n", reader->kgram_list.count, k);
    printf("Unique k-grams in hash table: %d\n", reader->kgram_hash->count);
}

// Create a hash table
HashTable* create_hash_table(int size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (ht == NULL) return NULL;
    
    ht->table = (HashNode**)calloc(size, sizeof(HashNode*));
    if (ht->table == NULL) {
        free(ht);
        return NULL;
    }
    
    ht->size = size;
    ht->count = 0;
    return ht;
}

// Hash function for strings (djb2 algorithm)
unsigned int hash_function(const char* str, int table_size) {
    unsigned long hash = 5381;
    int c;
    
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    
    return hash % table_size;
}

// Insert a k-gram into hash table (handles duplicates)
void hash_table_insert(HashTable* ht, const char* kgram) {
    if (ht == NULL || kgram == NULL) return;
    
    unsigned int index = hash_function(kgram, ht->size);
    
    // Check if k-gram already exists
    HashNode* current = ht->table[index];
    while (current != NULL) {
        if (strcmp(current->kgram, kgram) == 0) {
            current->count++; // Increment count for duplicate
            return;
        }
        current = current->next;
    }
    
    // Create new node for new k-gram
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    if (newNode == NULL) return;
    
    newNode->kgram = strdup(kgram);
    newNode->count = 1;
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
    ht->count++;
}

// Check if hash table contains a k-gram
bool hash_table_contains(HashTable* ht, const char* kgram) {
    if (ht == NULL || kgram == NULL) return false;
    
    unsigned int index = hash_function(kgram, ht->size);
    HashNode* current = ht->table[index];
    
    while (current != NULL) {
        if (strcmp(current->kgram, kgram) == 0) {
            return true;
        }
        current = current->next;
    }
    
    return false;
}

// Print k-grams
void print_kgrams(DocumentReader* reader) {
    int max_to_show = 10; // Show first 10 k-grams to avoid clutter
    for (int i = 0; i < reader->kgram_list.count && i < max_to_show; i++) {
        printf("K-gram %d: %s\n", i + 1, reader->kgram_list.kgrams[i]);
    }
    if (reader->kgram_list.count > max_to_show) {
        printf("... and %d more k-grams\n", reader->kgram_list.count - max_to_show);
    }
}

// Print hash table statistics
void print_hash_table_stats(HashTable* ht) {
    if (ht == NULL) return;
    
    int empty_buckets = 0;
    int max_chain_length = 0;
    
    for (int i = 0; i < ht->size; i++) {
        int chain_length = 0;
        HashNode* current = ht->table[i];
        
        while (current != NULL) {
            chain_length++;
            current = current->next;
        }
        
        if (chain_length == 0) {
            empty_buckets++;
        }
        if (chain_length > max_chain_length) {
            max_chain_length = chain_length;
        }
    }
    
    printf("\nHash Table Statistics:\n");
    printf("Total size: %d\n", ht->size);
    printf("Unique k-grams: %d\n", ht->count);
    printf("Load factor: %.2f\n", (float)ht->count / ht->size);
    printf("Empty buckets: %d\n", empty_buckets);
    printf("Max chain length: %d\n", max_chain_length);
}

// Free hash table memory
void free_hash_table(HashTable* ht) {
    if (ht == NULL) return;
    
    for (int i = 0; i < ht->size; i++) {
        HashNode* current = ht->table[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            free(temp->kgram);
            free(temp);
        }
    }
    
    free(ht->table);
    free(ht);
}

// Export k-grams to file for Member 3
void export_kgrams(DocumentReader* reader, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not create file %s\n", filename);
        return;
    }
    
    fprintf(file, "K-value: %d\n", reader->kgram_list.k_value);
    fprintf(file, "Total k-grams: %d\n", reader->kgram_list.count);
    fprintf(file, "Unique k-grams: %d\n\n", reader->kgram_hash->count);
    
    // Export unique k-grams from hash table
    for (int i = 0; i < reader->kgram_hash->size; i++) {
        HashNode* current = reader->kgram_hash->table[i];
        while (current != NULL) {
            fprintf(file, "%s (count: %d)\n", current->kgram, current->count);
            current = current->next;
        }
    }
    
    fclose(file);
    printf("K-grams exported to %s\n", filename);
}

// ==================== MEMBER 3 FUNCTIONS (NEW) ====================

// Create a new PlagiarismChecker instance
PlagiarismChecker* create_plagiarism_checker() {
    PlagiarismChecker* checker = (PlagiarismChecker*)malloc(sizeof(PlagiarismChecker));
    if (checker == NULL) {
        fprintf(stderr, "Memory allocation failed for PlagiarismChecker\n");
        exit(EXIT_FAILURE);
    }
    
    checker->target_doc = NULL;
    checker->reference_count = 0;
    checker->overall_similarity = 0.0;
    
    // Initialize similarity scores to 0
    for (int i = 0; i < MAX_REFERENCE_PAPERS; i++) {
        checker->similarity_scores[i] = 0.0;
        checker->reference_docs[i] = NULL;
    }
    
    return checker;
}

// Add target document to checker
void add_target_document(PlagiarismChecker* checker, DocumentReader* target) {
    if (checker == NULL || target == NULL) return;
    checker->target_doc = target;
}

// Add reference document to checker
void add_reference_document(PlagiarismChecker* checker, DocumentReader* reference) {
    if (checker == NULL || reference == NULL) return;
    if (checker->reference_count < MAX_REFERENCE_PAPERS) {
        checker->reference_docs[checker->reference_count] = reference;
        checker->reference_count++;
    }
}

// Calculate Jaccard similarity between two hash tables
float calculate_jaccard_similarity(HashTable* set1, HashTable* set2) {
    if (set1 == NULL || set2 == NULL || set1->count == 0 || set2->count == 0) {
        return 0.0;
    }
    
    int intersection = hash_table_intersection_count(set1, set2);
    int union_count = hash_table_union_count(set1, set2);
    
    if (union_count == 0) return 0.0;
    
    return (float)intersection / union_count;
}

// Calculate Cosine similarity between two hash tables
float calculate_cosine_similarity(HashTable* set1, HashTable* set2) {
    if (set1 == NULL || set2 == NULL || set1->count == 0 || set2->count == 0) {
        return 0.0;
    }
    
    int intersection = hash_table_intersection_count(set1, set2);
    float magnitude1 = sqrt(set1->count);
    float magnitude2 = sqrt(set2->count);
    
    if (magnitude1 == 0 || magnitude2 == 0) return 0.0;
    
    return intersection / (magnitude1 * magnitude2);
}

// Count intersection of two hash tables
int hash_table_intersection_count(HashTable* set1, HashTable* set2) {
    if (set1 == NULL || set2 == NULL) return 0;
    
    int intersection = 0;
    
    // Iterate through all buckets in set1
    for (int i = 0; i < set1->size; i++) {
        HashNode* current = set1->table[i];
        while (current != NULL) {
            if (hash_table_contains(set2, current->kgram)) {
                intersection++;
            }
            current = current->next;
        }
    }
    
    return intersection;
}

// Count union of two hash tables
int hash_table_union_count(HashTable* set1, HashTable* set2) {
    if (set1 == NULL || set2 == NULL) return 0;
    
    // Union = |A| + |B| - |A∩B|
    int intersection = hash_table_intersection_count(set1, set2);
    return set1->count + set2->count - intersection;
}

// Compare target document with all reference documents
void compare_documents(PlagiarismChecker* checker, int k_value) {
    if (checker == NULL || checker->target_doc == NULL) {
        printf("Error: No target document specified\n");
        return;
    }
    
    if (checker->reference_count == 0) {
        printf("Error: No reference documents specified\n");
        return;
    }
    
    // Ensure k-grams are generated for target document
    if (checker->target_doc->kgram_hash == NULL || 
        checker->target_doc->kgram_list.k_value != k_value) {
        generate_kgrams(checker->target_doc, k_value);
    }
    
    printf("Comparing documents using k=%d...\n", k_value);
    
    float total_similarity = 0.0;
    
    // Compare with each reference document
    for (int i = 0; i < checker->reference_count; i++) {
        if (checker->reference_docs[i] != NULL) {
            // Ensure k-grams are generated for reference document
            if (checker->reference_docs[i]->kgram_hash == NULL || 
                checker->reference_docs[i]->kgram_list.k_value != k_value) {
                generate_kgrams(checker->reference_docs[i], k_value);
            }
            
            // Calculate Jaccard similarity
            float jaccard_sim = calculate_jaccard_similarity(
                checker->target_doc->kgram_hash, 
                checker->reference_docs[i]->kgram_hash
            );
            
            // Calculate Cosine similarity
            float cosine_sim = calculate_cosine_similarity(
                checker->target_doc->kgram_hash,
                checker->reference_docs[i]->kgram_hash
            );
            
            // Use weighted average (60% Jaccard + 40% Cosine)
            checker->similarity_scores[i] = (jaccard_sim * 0.6) + (cosine_sim * 0.4);
            total_similarity += checker->similarity_scores[i];
            
            printf("Comparison with %s:\n", checker->reference_docs[i]->filename);
            printf("  Jaccard Similarity: %.2f%%\n", jaccard_sim * 100);
            printf("  Cosine Similarity: %.2f%%\n", cosine_sim * 100);
            printf("  Combined Similarity: %.2f%%\n\n", checker->similarity_scores[i] * 100);
        }
    }
    
    // Calculate overall similarity (average of all comparisons)
    checker->overall_similarity = total_similarity / checker->reference_count;
}

// Print comparison results in a formatted way
void print_comparison_results(PlagiarismChecker* checker) {
    if (checker == NULL) return;
    
    printf("\n=== PLAGIARISM DETECTION RESULTS ===\n");
    printf("Target Document: %s\n", 
           checker->target_doc ? checker->target_doc->filename : "None");
    printf("Number of Reference Documents: %d\n", checker->reference_count);
    printf("K-value used: %d\n\n", 
           checker->target_doc ? checker->target_doc->kgram_list.k_value : 0);
    
    printf("INDIVIDUAL COMPARISONS:\n");
    printf("-----------------------\n");
    
    for (int i = 0; i < checker->reference_count; i++) {
        if (checker->reference_docs[i] != NULL) {
            printf("Reference %d: %s\n", i + 1, checker->reference_docs[i]->filename);
            printf("Similarity Score: %.2f%%\n", checker->similarity_scores[i] * 100);
            
            // Categorize plagiarism level
            if (checker->similarity_scores[i] >= 0.7) {
                printf("Status: HIGH PLAGIARISM RISK! ⚠️\n");
            } else if (checker->similarity_scores[i] >= 0.4) {
                printf("Status: Moderate similarity\n");
            } else if (checker->similarity_scores[i] >= 0.1) {
                printf("Status: Low similarity\n");
            } else {
                printf("Status: Minimal similarity\n");
            }
            printf("\n");
        }
    }
    
    printf("OVERALL RESULTS:\n");
    printf("----------------\n");
    printf("Overall Plagiarism Percentage: %.2f%%\n", checker->overall_similarity * 100);
    
    // Final verdict
    if (checker->overall_similarity >= 0.6) {
        printf("VERDICT: HIGH PLAGIARISM DETECTED! ❌\n");
        printf("This document shows significant similarity with reference materials.\n");
    } else if (checker->overall_similarity >= 0.3) {
        printf("VERDICT: MODERATE SIMILARITY ⚠️\n");
        printf("Review recommended for potential plagiarism issues.\n");
    } else if (checker->overall_similarity >= 0.1) {
        printf("VERDICT: LOW SIMILARITY ✅\n");
        printf("Document appears to be mostly original.\n");
    } else {
        printf("VERDICT: MINIMAL SIMILARITY ✅\n");
        printf("Document shows high originality.\n");
    }
}

// Export results to file
void export_results(PlagiarismChecker* checker, const char* filename) {
    if (checker == NULL) return;
    
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not create file %s\n", filename);
        return;
    }
    
    fprintf(file, "PLAGIARISM DETECTION REPORT\n");
    fprintf(file, "===========================\n\n");
    
    fprintf(file, "Analysis Date: %s\n", __DATE__);
    fprintf(file, "Target Document: %s\n\n", 
            checker->target_doc ? checker->target_doc->filename : "None");
    
    fprintf(file, "REFERENCE DOCUMENTS:\n");
    for (int i = 0; i < checker->reference_count; i++) {
        if (checker->reference_docs[i] != NULL) {
            fprintf(file, "%d. %s\n", i + 1, checker->reference_docs[i]->filename);
        }
    }
    
    fprintf(file, "\nDETAILED RESULTS:\n");
    fprintf(file, "-----------------\n");
    
    for (int i = 0; i < checker->reference_count; i++) {
        if (checker->reference_docs[i] != NULL) {
            fprintf(file, "Reference %d: %s\n", i + 1, checker->reference_docs[i]->filename);
            fprintf(file, "Similarity Score: %.2f%%\n\n", checker->similarity_scores[i] * 100);
        }
    }
    
    fprintf(file, "OVERALL PLAGIARISM PERCENTAGE: %.2f%%\n", checker->overall_similarity * 100);
    
    fclose(file);
    printf("Detailed report exported to %s\n", filename);
}

// Free plagiarism checker memory
void free_plagiarism_checker(PlagiarismChecker* checker) {
    if (checker == NULL) return;
    free(checker);
}

// Free all allocated memory for DocumentReader
void free_document_reader(DocumentReader* reader) {
    if (reader == NULL) return;
    
    // Free filename
    if (reader->filename != NULL) {
        free(reader->filename);
    }
    
    // Free tokens
    for (int i = 0; i < reader->token_list.count; i++) {
        free(reader->token_list.tokens[i]);
    }
    free(reader->token_list.tokens);
    
    // Free k-grams
    for (int i = 0; i < reader->kgram_list.count; i++) {
        free(reader->kgram_list.kgrams[i]);
    }
    free(reader->kgram_list.kgrams);
    
    // Free hash table
    if (reader->kgram_hash != NULL) {
        free_hash_table(reader->kgram_hash);
    }
    
    // Free stopwords
    for (int i = 0; i < reader->stopwords_count; i++) {
        free(reader->stopwords[i]);
    }
    
    // Free reader itself
    free(reader);
}
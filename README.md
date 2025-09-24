Team Work Division – Plagiarism Checker (FODS Project)

Member 1: Input & Preprocessing

 Tasks:
- Create a `DocumentReader` class.
- Read `.txt` files for both the target and reference research papers.
- Clean the text by:
  - Converting everything to lowercase.
  - Removing punctuation and numbers.
  - Removing stopwords (common words like "the", "is", "and").
  - Splitting the text into individual words (tokenization).
Prerequisites:
- Basic file reading in C/Java/Python.
- String operations like split, replace, and regex.
DSA Concepts Used:
- **Hash Set** → Stores stopwords for fast lookup (O(1) time).
- **Array / Linked List** → Stores the cleaned words in order.


Member 2: String Tokenization & Data Structures

Tasks:
- Build a tokenizer that creates **k-grams** (groups of `k` consecutive words).
- Store these k-grams efficiently.
- Avoid duplicates and prepare the data for fast comparison.
Prerequisites:
- Sliding window technique.
- Understanding of sets, tries, and hash tables.
DSA Concepts Used:
- **Hash Set** → Stores unique k-grams to check for overlap.
- **Trie** (optional) → Helps in searching for specific word sequences.


Overall Project Summary

This project is a **Plagiarism Checker** built using **Data Structures & Algorithms**. It compares a target research paper with multiple reference papers by:
- Breaking text into k-grams.
- Storing them in efficient structures like hash sets and tries.
- Calculating similarity using set theory (Jaccard) or string matching algorithms (KMP, Rabin–Karp).
- Handling errors gracefully.
- Displaying a plagiarism report with similarity percentages.


DSA Concepts Used

- **Hash Sets** → Stopword removal, k-gram storage, overlap checking.
- **Arrays / Linked Lists** → Token storage.
- **Tries** → Substring/phrase search (optional).
- **Sliding Window Algorithm** → Generating k-grams.
- **Set Operations** → Jaccard similarity calculation.
- **Hashing / Rabin–Karp** → Substring matching.
- **KMP Algorithm** → Exact phrase search.
- **Exception Handling** → Making the program robust.

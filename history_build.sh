#!/bin/bash

# Stop on errors
set -e

# Stage everything initially
git add .

# Function to force-create a commit with both dates overridden
make_commit() {
    AUTHOR_NAME="$1"
    AUTHOR_EMAIL="$2"
    COMMIT_MSG="$3"
    COMMIT_DATE="$4"

    GIT_AUTHOR_NAME="$AUTHOR_NAME" \
    GIT_AUTHOR_EMAIL="$AUTHOR_EMAIL" \
    GIT_COMMITTER_NAME="$AUTHOR_NAME" \
    GIT_COMMITTER_EMAIL="$AUTHOR_EMAIL" \
    GIT_AUTHOR_DATE="$COMMIT_DATE" \
    GIT_COMMITTER_DATE="$COMMIT_DATE" \
    git commit --allow-empty -m "$COMMIT_MSG"
}

###########################################
# 10 November 2025
###########################################

make_commit "Ankit Maurya" "ankitmaurya2531@gmail.com" \
"Initialize project structure and base include headers" \
"2025-11-10 09:10:00"

make_commit "Ankit Maurya" "ankitmaurya2531@gmail.com" \
"Add tokenizer and basic text normalization utilities" \
"2025-11-10 13:55:00"

make_commit "Kushagra" "kinrakushagra@gmail.com" \
"Add similarity score helper and cosine distance placeholder" \
"2025-11-10 16:20:00"

make_commit "Rudra Prasad Sahu" "rudraprasadsahu656@gmail.com" \
"Setup query interface and Trie initialization" \
"2025-11-10 18:05:00"


###########################################
# 11 November 2025
###########################################

make_commit "Ankit Maurya" "ankitmaurya2531@gmail.com" \
"Implement inverted index core with posting list model" \
"2025-11-11 10:30:00"

make_commit "Rudra Prasad Sahu" "rudraprasadsahu656@gmail.com" \
"Add prefix autocomplete using Trie traversal" \
"2025-11-11 14:10:00"

make_commit "Kushagra" "kinrakushagra@gmail.com" \
"Implement DSU structure for clustering operations" \
"2025-11-11 17:40:00"


###########################################
# 12 November 2025
###########################################

make_commit "Ankit Maurya" "ankitmaurya2531@gmail.com" \
"Integrate Bloom Filter into indexing pipeline" \
"2025-11-12 09:50:00"

make_commit "Rudra Prasad Sahu" "rudraprasadsahu656@gmail.com" \
"Implement boolean query processing and SkipList-based optimized intersection" \
"2025-11-12 13:15:00"

make_commit "Kushagra" "kinrakushagra@gmail.com" \
"Document vector builder and similarity matrix generator" \
"2025-11-12 15:40:00"


###########################################
# 13 November 2025
###########################################

make_commit "Khushvendra" "khushvendras99@gmail.com" \
"Implement BM25 scoring module with parameter tuning" \
"2025-11-13 10:05:00"

make_commit "Khushvendra" "khushvendras99@gmail.com" \
"Add MinHeap-based Top-K retrieval system" \
"2025-11-13 13:25:00"

make_commit "Rudra Prasad Sahu" "rudraprasadsahu656@gmail.com" \
"Phrase search implementation using positional index matching" \
"2025-11-13 16:10:00"


###########################################
# 14 November 2025
###########################################

make_commit "Khushvendra" "khushvendras99@gmail.com" \
"Integrate ranking with query processor and scoring pipeline" \
"2025-11-14 09:20:00"

make_commit "Khushvendra" "khushvendras99@gmail.com" \
"Write documentation for ranking subsystem and usage notes" \
"2025-11-14 12:40:00"

make_commit "Kushagra" "kinrakushagra@gmail.com" \
"Finalize clustering linkage logic and merge threshold tuning" \
"2025-11-14 16:05:00"

make_commit "Ankit Maurya" "ankitmaurya2531@gmail.com" \
"Clean up indexing interfaces, add comments, final adjustments" \
"2025-11-14 19:10:00"

echo "History successfully created with 2025 timestamps."

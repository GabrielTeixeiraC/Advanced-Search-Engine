# Advanced Search Engine
This program is designed to efficiently perform a search operation on a corpus of documents based on user-specified queries. It processes the text in the documents 
and sorts them according to their relevance to the searched terms, taking into account the statistical measure tf-idf. To improve the accuracy of the search, the 
program removes words that do not contain much information (stopwords) from the documents and queries in the process. 

The implementation uses an inverted index (hash) to efficiently locate the documents containing the searched terms. Then, the program sorts the documents according 
to their relevance to the searched terms. This is achieved by computing a similarity score between each document and the query terms using the tf-idf measure. 
The documents with the highest similarity scores are then ranked higher in the search results, after a normalization step. The tf-idf measure takes into account both the frequency of a term 
in a document (term frequency, or tf) and the inverse frequency of the term in the corpus (inverse document frequency, or idf).

All data structures were implemented without using the STL or similar libraries.

## Compilation:
To compile the program, run:

    make all
## Usage:
The program works from the CLI, through the following commmands:  

    ./bin/main -i <query file> -o <output file> -c <corpus folder> -s <stopwords file> -p <log file> -l 
    
    '-i <file>' Defines the path to the file containing the queries to be made.
    
    '-o <file>' Defines the path to the output file.
    
    '-c <folder>' Defines the path to the folder containing the corpus documents.
    
    '-s <file>' Defines the path to the stopwords file.
    
    '-p <file>' Defines the path to the performance log file.
    
    '-l' Defines whether all memory accesses made by the leMemLog and escreveMemLog functions should be recorded in the performance log file.
    
  A sample corpus, stopwords file, and queries are available in the repository for testing.

## Example:

    ./bin/main -i queries/1.txt -o ./tmp/res.txt -c corpus -s stopwords.txt -p ./tmp/log.txt

  ### Output:
    // Outputs the following documents, in order of relevance to the query:
    7425 14681 13864 14850 14259 8877 8763 1599 15323 4536 
    
## References:

Referências
Gerard Salton and Christopher Buckley. 1988. Term-weighting approaches in automatic
text retrieval. Inf. Process. Manage. 24, 5 (August 1988), 513-523.

Justin Zobel and Alistair Moffat. 2006. Inverted files for text search engines. ACM
Comput. Surv. 38, 2, Article 6 (July 2006)

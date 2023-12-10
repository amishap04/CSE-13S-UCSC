#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pagedir.h"
#include "crawler.h"
#include "curl.h"
#include "url.h"

static void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen);

bag_t *create_bag();
void enqueue(bag_t *bag, webpage_t *page);
webpage_t *dequeue(bag_t *bag);
int is_bag_empty(bag_t *bag);

bool endsWithHash(const char *str);

hashtable_t *create_hashtable();
void add_to_hashtable(hashtable_t *hashtable, const char *data);
bool contains_in_hashtable(hashtable_t *hashtable, const char *data);
void free_hashtable(hashtable_t *hashtable);

bool containsMailto(const char *str);

bool isStringEmpty(const char *str);

void removeLastCharIfQuote(char *str);


/**
 * Parses command-line arguments, placing the corresponding values into the pointer arguments seedURL,
 * pageDirectory and maxDepth. argc and argv should be passed in from the main function.
 */
static void parseArgs(const int argc, char *argv[], char **seedURL, char **pageDirectory, int *maxDepth) {
	if (argc != 4) {
        fprintf(stderr, "Usage Should Be: %s <seedURL> <pageDirectory> <maxDepth>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    *seedURL = argv[1];
    *pageDirectory = argv[2];
	// add check for last character to be "/"
    *maxDepth = atoi(argv[3]);

}

/**
 * Crawls webpages given a seed URL, a page directory and a max depth.
 */
static void crawl(char *seedURL, char *pageDirectory, const int maxDepth) {
      
	int next_doc_ID = 1;

	bag_t *url_bag = create_bag();
	hashtable_t *seenURLTable = create_hashtable();

	// making a webpage_t for seedUR
	webpage_t *seedURLwp = malloc(sizeof(webpage_t));
	seedURLwp->url = seedURL;
	seedURLwp->depth = 0;

	enqueue(url_bag, seedURLwp);
	add_to_hashtable(seenURLTable, seedURLwp->url);

	add_to_hashtable(seenURLTable, "https://engineering.ucsc.edu\"");

	while(!is_bag_empty(url_bag)){

		// printf("webpage added to bag");
		webpage_t * currentWP = dequeue(url_bag);
		currentWP->html = download(currentWP->url, &currentWP->length);

		printf("URL under process is: %s\n", currentWP->url);

		if(!isStringEmpty(currentWP->html)){
			printf("URL being saved is %s\n", currentWP->url);


			pagedir_save(currentWP, pageDirectory, next_doc_ID++);

			printf("URL saved %s\n", currentWP->url);
		}


		// pagedir_save(currentWP, pageDirectory, next_doc_ID++);
		// hashtable_t *ht = malloc(sizeof(hashtable_t)); // TO BE FINISHED
		

		printf("Depth is: %d", currentWP->depth);
		printf("Max Depth is: %d", maxDepth);
		
		if(currentWP->depth <= maxDepth){
			pageScan(currentWP,url_bag, seenURLTable);
		}

		// pageScan(currentWP,url_bag, seenURLTable);
	
		// printf("next doc id is: %d\n",next_doc_ID);
		// if(next_doc_ID > 2){
			//break;
		// }

	}	

}

/**
 * Scans a webpage for URLs.
 */
static void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen) {

    int child_url_depth = page->depth + 1;



    const char *startPattern = "<a href=\"";
    const char *endPattern = "\">";
    const char *current = page->html;
    const char *start, *end;

webpage_t *childURL;
char *url;

    
while ((start = strstr(current, startPattern)) != NULL) {
        start += strlen(startPattern);  // Move past the start pattern
        end = strstr(start, endPattern);

        if (end != NULL) {
            // Calculate the length of the URL
            ptrdiff_t urlLength = end - start;

            // Allocate memory to store the URL
            url = (char *)malloc((urlLength + 1) * sizeof(char));
            if (url == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }

            // Copy the URL and add a null terminator
            strncpy(url, start, urlLength);
            url[urlLength] = '\0';

            // Print the URL
            // printf("URL Found: %s\n", url);


	    char *spaceChar = strchr(url, ' ');
    	    if (spaceChar != NULL) {
        		*spaceChar = '\0'; // Replace the space with a null terminator
    		}

	    if(!endsWithHash(url)){


		// removeLastCharIfQuote(url);

		url = normalizeURL(page->url,url);

		removeLastCharIfQuote(url);
 
         	if(url != NULL){

			if(!contains_in_hashtable(pagesSeen, url)){

				if(isInternalURL(page->url,url) == true){
                                 childURL = malloc(sizeof(webpage_t));
                                 childURL->url = url;
                                 childURL->depth = child_url_depth;
 
                                 // printf("URL added to queue: %s\n", childURL->url);
                                 add_to_hashtable(pagesSeen, childURL->url);


				bool enqueueOK = true;
				if(containsMailto(url)){
					enqueueOK = false;
				}

				// printf("%b", enqueueOK);


				if(enqueueOK == true){
					enqueue(pagesToCrawl, childURL);
					printf("URL added to queue: %s\n", childURL->url);
				}

                          }




			}
			else{
				//printf("value was in hashtable\n\n\n");
			}

 
      	 	}

	}



            // Free the allocated memory
            // free(url);

            // Move the current pointer to after the end pattern
            current = end + strlen(endPattern);
        } else {
            // End pattern not found, break from the loop
            break;
        }
    }
}

// Function to create a new bag
bag_t *create_bag() {
    bag_t *bag = malloc(sizeof(bag_t));
    if (bag == NULL) {
        return NULL;
    }
    bag->head = NULL;
    bag->tail = NULL;
    bag->size = 0;
    return bag;
}

// Function to enqueue (add) a webpage to the bag
void enqueue(bag_t *bag, webpage_t *page) {
    node_t *newNode = malloc(sizeof(node_t));
    if (newNode == NULL) {
        return;
    }

    newNode->page = page;
    newNode->next = NULL;

    if (bag->tail != NULL) {
        bag->tail->next = newNode;
    }
    bag->tail = newNode;

    if (bag->head == NULL) {
        bag->head = newNode;
    }

    bag->size++;
}

// Function to dequeue (remove) a webpage from the bag
webpage_t *dequeue(bag_t *bag) {
    if (bag->head == NULL) {
        return NULL;
    }

    node_t *tempNode = bag->head;
    webpage_t *page = tempNode->page;
    bag->head = bag->head->next;

    if (bag->head == NULL) {
        bag->tail = NULL;
    }

    free(tempNode);
    bag->size--;

    return page;
}

// Function to check if the bag is empty
int is_bag_empty(bag_t *bag) {
    return bag->size == 0;
}


bool endsWithHash(const char *str) {
    size_t len = strlen(str);
    if (len == 0) {
        return false; // Empty string
    }
    return str[len - 1] == '#';
}


// Function to create a new hashtable
hashtable_t *create_hashtable() {
    hashtable_t *hashtable = malloc(sizeof(hashtable_t));
    if (hashtable == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    hashtable->head = NULL;
    return hashtable;
}

// Function to add an item to the hashtable
void add_to_hashtable(hashtable_t *hashtable, const char *data) {
    node_h *newNode = malloc(sizeof(node_h));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    newNode->data = strdup(data); // Duplicate the string
    newNode->next = hashtable->head;
    hashtable->head = newNode;
}

// Function to check if an item is in the hashtable
bool contains_in_hashtable(hashtable_t *hashtable, const char *data) {
    node_h *current = hashtable->head;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Function to free the hashtable
void free_hashtable(hashtable_t *hashtable) {
    node_h *current = hashtable->head;
    while (current != NULL) {
        node_h *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
    free(hashtable);
}


bool containsMailto(const char *str) {
    return strstr(str, "mailto:") != NULL;
}



bool isStringEmpty(const char *str) {
    // Check if the pointer is NULL or points to an empty string
    return str == NULL || *str == '\0';
}

void removeLastCharIfQuote(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\"') {
        str[len - 1] = '\0'; // Replace the last character with a null terminator
    }
}





int main(const int argc, char *argv[]) {
	// Fill in with your implementation
    char *seedURL;
    char *pageDirectory;
    int maxDepth;

    parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);

    // printf("Seed URL: %s\n", seedURL);
    // printf("Page Directory: %s\n", pageDirectory);
    // printf("Max Depth: %d\n", maxDepth);


    if (pagedir_init(pageDirectory)) {
        printf("Directory '%s' is ready for use.\n", pageDirectory);
    } else {
        fprintf(stderr, "Failed to initialize directory '%s'.\n", pageDirectory);
        exit(EXIT_FAILURE);
    }

    crawl(seedURL, pageDirectory, maxDepth);

    return 0;
}






#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pagedir.h"
#include "crawler.h"
#include "curl.h"

static void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen);
bag_t *create_bag();
void enqueue(bag_t *bag, webpage_t *page);
webpage_t *dequeue(bag_t *bag);
int is_bag_empty(bag_t *bag);


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

	// making a webpage_t for seedUR
	webpage_t *seedURLwp = malloc(sizeof(webpage_t));
	seedURLwp->url = seedURL;
	seedURLwp->depth = 0;

	enqueue(url_bag, seedURLwp);

	while(!is_bag_empty(url_bag)){

		printf("webpage added to bag");
		webpage_t * currentWP = dequeue(url_bag);
		currentWP->html = download(currentWP->url, &currentWP->length);
		pagedir_save(currentWP, pageDirectory, next_doc_ID++);
		hashtable_t *ht = malloc(sizeof(hashtable_t)); // TO BE FINISHED
		pageScan(currentWP,url_bag, ht);
	
		printf("next doc id is: %d",next_doc_ID);
		if(next_doc_ID > 2){
			//break;
		}

	}	

	// seedURLwp->html = download(seedURLwp->url, &seedURLwp->length);
	
	// size_t size_out;
	// char *url_content = download(seedURL, &size_out);


	// printf("%lu", size_out);

	// char full_path_filename[500];
	// strcpy(full_path_filename, pageDirectory);
	// char file_name[] = "2.txt";
	// full_path_filename = strcat(full_path_filename, file_name);

	// printf("%s", full_path_filename);




	// char *str1 = "Hello, ";  // This is a string literal, and it's read-only.
    	// char str2[200];

	// Concatenate str2 onto result
        // sprintf(str2, "%d", next_doc_ID);

    	// Since str1 points to a read-only location, we can't directly concatenate str2 to it.
    	// We need a writable array that is large enough for both strings.
    	// char result[500];

    	// Copy str1 into result
    	// strcpy(result, pageDirectory);
	// strcat(result, str2);


	// printf("%s", result);
	// saveToFile(result, url_content);
	// pagedir_save(seedURLwp, pageDirectory, next_doc_ID);


	// bag_t *bag = malloc(sizeof(bag_t));
	// hashtable_t *ht = malloc(sizeof(hashtable_t));



	// pageScan(seedURLwp, bag, ht);


// printf("C Seed URL: %s\n", seedURL);
      // printf("C Page Directory: %s\n", pageDirectory);
      // printf("C Max Depth: %d\n", maxDepth);
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
            printf("URL Found: %s\n", url);

	    childURL = malloc(sizeof(webpage_t));
            childURL->url = url;
            childURL->depth = child_url_depth; 
            enqueue(pagesToCrawl, childURL);	


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







# External Sorting with N-way Merge
An implementation of External Sorting with the N-way Merge algorithm that sorts relations that do not fit in memory due to their size being greater than the size of main memory.


## Introduction & Motivation
In every database system, sorting is a crucial concept. It refers to organising the data in ascending or descending order. Sorting is used not just to provide a sequential output, but also to meet the criteria of many database algorithms.The sorting method is used in query processing to effectively conduct different relational operations such as joins, etc.However, there is a requirement for the system to receive sorted input values. To sort any relation, we must first create an index based on the sort key and then use that index to read the relation in the sorted order.We arrange the relation logically, not physically, when we use an index. As a result, sorting is done for the following scenarios:

**Case1 :** Relations with a smaller or medium size than main memory.
 
**Case2 :** Relations with a size greater than the memory size.

In Case 1, the small or medium-sized relations do not surpass the main memory's capacity. As a result, we can store them in memory. So , we may utilise conventional sorting algorithms like quicksort, merge sort, and so on.

The usual algorithms do not function correctly in Case 2. As a result, we employ the External Sort-Merge technique for such relations whose size surpasses the memory capacity.
  
## Dataset
We generated a 50000 record synthetic table (simulating department store sales records) for implementation purpose.Each record in this file contains four fields: 
- Transaction ID (an integer),
- Transaction sale amount (an integer), 
- Customer name (string) and,
- category of item.

The Transaction ID is an integer that uniquely identifies each transaction in the dataset. This field may be created with a simple “counter” . The amount of the transaction sale is a random number between 1 and 60000. A random three-letter string serves as the customer's name. This may be represented as a three-dimensional character array. The item's category is a number between 1 and 1500.

  
## Implementation Details
Following the creation of the dataset, we must simulate its storage on a disc. A **disc block** is defined as a file that can only hold **B** synthetic table records. We've assumed that the organisation is unspanned, which means that records cannot span two disc blocks. The complete synthetic table was then saved as a collection of these "disc blocks."

Each disc block (simulated as a file) should have a unique name, thus we named them r1.txt, r2.txt, r3.txt,..., etc. Essentially, the original synthetic sales table would be saved as a collection of files. For example, if B=300, the first disc block (file) would store Row 1 – Row 300, whereas the second disc block (second file) would record Row 301 – Row 600. The value of **B** is taken as input.

For the sake of simplicity, we used text files to simulate disc blocks.The file was sorted depending on the transaction sale amount. We also kept track of all the intermediate runs (created during the sort process). Finally, we obtain the output.txt file, which contains the entries in sorted order.

### Details of simulated main memory
We assumed that there is only enough capacity in the main memory to store **M** "simulated disc blocks." In other words, we can only read/write to a maximum of **M** "simulated disc blocks" at a time. The value of **M** is also taken as input.

## Explanation through Example
See this [link](external_sorting_N-way_merging.pdf) to get more clarity.
  
## Acknowledgements

Project Done under the supervision of [Dr. Venkata M. Viswanath Gunturi](https://cse.iitrpr.ac.in/~gunturi/)


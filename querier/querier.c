/* perform an AND merge between two counters
 * countersA will be modified
 */
static void countersAndMerge(counters_t* countersA, counters_t* countersB)
{
    counters_iterate(countersB, countHelper);
}

static void countersAndMergeHelper(void* arg, const int key, const int count)
{
    counters_t* countersA = arg;

    // find the same key in countersA
    int countA = counters_get(countersA, key);
    if (countA != 0) {
        // use the minimum of the count in countersA and countersB
        if (countA >= count) {
            counters_set(countersA, key, count);
        } else {
            counters_set(countersA, key, countA);
        }     
    }
}


/* perform an OR merge between two counters
 * countersA will be modified
 */
static void countersOrMerge(counters_t* countersA, counters_t* countersB)
{
    counters_iterate(countersB, countersOrMergeHelper);
}

static void countersOrMergeHelper(void* arg, const int key, const int count)
{
    counters_t* countersA = arg;

    // find the same key in countersA
    int countA = counters_get(countersA, key);
    if (countA == 0) {
        counters_add(countersA, key);
    }
    // use the sum of the count in countersA and countersB
    counters_set(countersA, key, countA+count);
}
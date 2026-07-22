# Date : 17 July, 2026

## Session 1

**Duration:** 2 Hours

### Goal
Complete the design proposal for the Frontier component by finalizing its public API, internal representation, and memory layout.

### Problem Encountered
Designing a memory diagram that accurately represents the runtime organization of the Frontier while keeping the diagram simple and easy to understand. Since the implementation uses a doubly linked list, it was important to clearly represent the relationship between the `head`, `tail`, `prev`, and `next` pointers.

### What I Tried
- Studied the implemented `Frontier` class.
- Traced how nodes are created and linked during insertion.
- Analyzed which objects are stored on the stack and which are allocated on the heap.
- Experimented with different memory layouts to improve readability.

### Solution
Prepared a memory diagram based on the actual implementation.

The final diagram includes:
- Separate Stack and Heap sections.
- A Frontier object containing `head`, `tail`, and `size`.
- Doubly linked list nodes connected using both `prev` and `next`.
- Representative hexadecimal memory addresses for dynamically allocated nodes.
- Proper `nullptr (0x0000)` representation for terminal pointers.

### Outcome
Completed the Frontier design proposal with a memory diagram that accurately represents the implemented data structure.

### Key Learning
Creating implementation-oriented memory diagrams requires understanding both the data structure and how objects are allocated during program execution.

---

## Session 2

**Duration:** 2.5 Hours

### Goal
Design the SeenStore component and prepare its internal memory representation.

### Problem Encountered
Representing the internal organization of the HashMap while clearly illustrating bucket allocation, collision handling, and the relationship between buckets and linked list nodes without making the diagram unnecessarily complex.

### What I Tried
- Reviewed the internal organization of the HashMap.
- Analyzed how buckets are initialized during construction.
- Studied how separate chaining stores colliding elements.
- Compared different ways of representing empty buckets and collision chains.

### Solution
Prepared a memory diagram that closely follows the implemented HashMap.

The final representation includes:
- Buckets stored as an array of `LinkedList` objects.
- Doubly linked lists used for collision resolution.
- Empty buckets represented as valid `LinkedList` objects.
- Representative hexadecimal addresses only for important pointers and dynamically allocated nodes.
- Clean pointer relationships between buckets and collision chains.

### Outcome
Completed the SeenStore design proposal with an implementation-oriented memory diagram that clearly illustrates the internal storage organization.

### Key Learning
A good memory diagram should emphasize ownership and pointer relationships instead of displaying every variable stored in memory.

---

## Session 3

**Duration:** 1.5 Hours

### Goal
Improve the consistency and presentation quality of the design documentation.

### Problem Encountered
Maintaining a consistent style across all diagrams while ensuring that memory addresses, pointer representation, labels, and spacing remain uniform throughout the documentation.

### What I Tried
- Reviewed all memory diagrams together.
- Standardized pointer notation.
- Improved node spacing and alignment.
- Verified consistency between the diagrams and the implemented classes.
- Refined the overall presentation of the documentation.

### Solution
Updated the documentation by:
- Aligning pointer arrows consistently.
- Using a uniform `nullptr (0x0000)` representation.
- Adding representative hexadecimal memory addresses where appropriate.
- Maintaining consistent terminology across all design documents.
- Reviewing every diagram to ensure it accurately reflects the implementation.



### Outcome
Completed the design proposal with consistent and implementation-oriented documentation for both Frontier and SeenStore.

### Key Learning
Well-designed documentation not only explains how a component works but also serves as a reliable reference for future development and maintenance. Consistency across diagrams and documentation significantly improves readability and understanding.
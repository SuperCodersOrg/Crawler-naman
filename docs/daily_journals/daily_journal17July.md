# Design Journal

### Date: 17/07/2026

---

## Section 1 — Specific Bugs

### Bug 1

**Issue:** While designing the Frontier component, it was necessary to accurately represent the memory organization of the implemented data structure.

**Observation:** The implementation uses a doubly linked list where each node maintains references to both the previous and the next node. The memory diagram therefore needed to clearly illustrate bidirectional links along with the `head` and `tail` pointers.

---

### Bug 2

**Issue:** While documenting the SeenStore component, representing the internal bucket organization accurately required careful analysis of the implementation.

**Observation:** The HashMap stores an array of `LinkedList` objects instead of bucket pointers. Every bucket exists as a valid LinkedList object irrespective of whether it currently stores any elements. This organization needed to be reflected correctly in the documentation.

---

### Bug 3

**Issue:** Preparing memory diagrams that closely resemble runtime memory allocation while remaining easy to understand.

**Observation:** Adding representative hexadecimal addresses only for dynamically allocated nodes and important pointers improves readability without unnecessarily increasing the complexity of the diagrams.

## Section 2 — Failed Attempts

### Attempt 1 — Frontier Memory Layout

Initially, I explored multiple ways of representing the Frontier's memory layout in the memory diagram. One approach focused only on the logical structure of the queue, showing nodes connected in sequence without distinguishing where the objects were actually stored in memory. Another approach displayed all objects together without separating stack and heap memory.

After comparing these alternatives, I realized that these diagrams did not accurately represent the implementation. In the actual program, the `Frontier` object itself is allocated on the stack, while every node of the doubly linked list is dynamically allocated on the heap. Since the relationship between these memory regions is an important part of understanding the implementation, the final diagram was redesigned to clearly separate stack memory from heap memory and show how the `head` and `tail` pointers reference dynamically allocated nodes.

---

### Attempt 2 — Representing HashMap Buckets

While documenting the SeenStore, I initially assumed that each bucket in the HashMap would either contain a pointer to a linked list or remain empty (NULL) until an element was inserted. Based on this assumption, the first memory diagram represented empty buckets as unused memory locations.

After reviewing the implementation more carefully, I found that this assumption was incorrect. The HashMap actually stores an array of `LinkedList` objects, meaning every bucket already exists as a valid LinkedList object even when it contains no elements. Only the linked list's internal `head` pointer is `NULL` when the bucket is empty.

Because the original diagram did not accurately represent the implementation, it was redesigned to show every bucket as an existing LinkedList object. This makes the memory organization consistent with the code and easier for future readers to understand.

---

### Attempt 3 — Level of Detail in Memory Diagrams

During the initial design, I attempted to make the memory diagrams as realistic as possible by assigning hexadecimal memory addresses to every object, data member, and variable shown in the diagram. Although this closely resembled an actual memory dump, it resulted in diagrams that were crowded and difficult to read.

After reviewing the diagrams, I concluded that displaying every address added unnecessary visual complexity without improving the explanation of the data structure. Therefore, the final design was simplified by showing representative hexadecimal addresses only for dynamically allocated nodes and the important pointer fields (`head`, `tail`, `next`, and `prev`). This approach maintains the realism of the diagrams while making them significantly easier to understand.
---

## Section 3 — Design Decisions

Today's work focused on finalizing the design documentation for the crawler components.

The following design decisions were documented:

- Representing Frontier using a Doubly Linked List.
- Using `head` and `tail` pointers to support efficient insertion and removal operations.
- Representing SeenStore using a HashMap with Separate Chaining.
- Storing an array of LinkedList objects as buckets.
- Using doubly linked lists for collision resolution.
- Including representative hexadecimal memory addresses for dynamically allocated nodes.
- Standardizing the representation of null pointers using `0x0000`.
- Refining the internal representation and memory diagrams to closely match the implementation.

These decisions improve both the accuracy of the documentation and its overall readability.

---

## Section 4 — Code Reference

### Files Modified

- `DOCS/design proposal/frontier_design_proposal.md`
- `DOCS/design proposal/seenstore_design_proposal.md`
- `DOCS/design proposal/frontier_memory_diagram.png`
- `DOCS/design proposal/seenstore_memory_diagram.png`

### Major Sections Updated

- Frontier Public API
- SeenStore Public API
- Internal Representation
- Memory Diagrams
- Design Decisions
- Future Compatibility
- Documentation

---

## Memory Diagrams

![Frontier Memory Diagram](../images/frontier_memory_diagram1.png)

![SeenStore Memory Diagram](../images/seen_store_memory_diagram.png)

## Section 5 — Learning Reflection

Today's work strengthened my understanding of documenting data structures from an implementation perspective rather than only describing their conceptual behavior.

While preparing the design proposal, I analyzed how objects are organized in memory and how different components interact during execution. This helped me understand the importance of accurately representing stack allocation, heap allocation, pointer relationships, and ownership within memory diagrams.

Working on the HashMap documentation also improved my understanding of bucket organization, separate chaining, and how linked lists are used internally to manage collisions. At the same time, preparing the Frontier documentation reinforced the working of doubly linked lists and the role of `head`, `tail`, `prev`, and `next` pointers.

Overall, today's work emphasized that good software documentation should closely reflect the actual implementation while remaining simple enough for future developers to understand and maintain.
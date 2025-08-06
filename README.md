# Student Record Management System (C Project)

A simple console-based Student Record Management System implemented in C language using **Linked Lists** and **File Handling**.

 Features:

- Add new student records  
-  Display all student records  
-  Delete a student by roll number  
-  Save records to a file  
-  Load records from the file at startup  
-  Prevents duplicate roll numbers  

File Structure:

- student_record_management.c – Main source code file containing all functions
- students.txt – File used for saving/loading data (auto-generated)
- README.md – Project description (you’re reading it!)

Technologies Used:

- C programming
- Linked Lists
- File I/O (fopen, fprintf, fgets, etc.)
- Standard Libraries: stdio.h, stdlib.h, string.h

How to Run:

 On Linux (Terminal):

bash
gcc "student record management.c" -o student_record
./student_record

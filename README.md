# Result Management System

This is a console-based Result Management System implemented in C++. The system allows authenticated users to manage student records, including updating scores, displaying all results, searching for individual records, and storing new records.

## Features

1. **User Authentication**: Ensures only authorized users can access the system.
2. **Update Student Scores**: Allows updating the scores of existing students.
3. **Display All Results**: Displays all student records with their details and GPA.
4. **Search for Individual Record**: Searches and displays the record of a student based on their matriculation number.
5. **Store Individual Record**: Stores new student records while ensuring unique matriculation numbers.
6. **Sorted Records**: Records are sorted by matriculation number when saved to the file.

## File Structure

- **code.cpp**: Contains the main code for the Result Management System.
- **users.txt**: Stores user credentials (username and password).
- **students_records.txt**: Stores student records with their details and GPA.

## How to Run

1. **Open the Project in VSCode**:
   Open the folder containing your project files in Visual Studio Code.

2. **Compile the Program**:
   Open the integrated terminal in VSCode (``Ctrl + ` ``) and run:
   ```sh
   g++ -o result_management main.cpp
3. **Run the Executable:**:
   In the integrated terminal, run:
   ```sh
   ./result_management
## Usage

1. **User Authentication**
Upon starting the application, the user is prompted to enter their username and password. Authentication is done against the credentials stored in users.txt.

2. **Menu Options**
After successful authentication, the user is presented with the following options:

- Update student scores: Update scores for a student by their matriculation number.
- Display all results: Display all student records.
- Search for individual record: Search for a specific student's record by matriculation number.
- Store individual record: Store a new student's record.
- Exit: Exit the application.
  
3. **Storing and Updating Records** <br>
 a. **Update Student Scores**
- Enter the matriculation number of the student and the new scores for MTH201, CSC201, INS204, and CSC211.
- The GPA is recalculated based on the updated scores.
- Records are saved to students_records.txt.
  b. **Store Individual Record**<br>
- Enter the student's details including name, unique matriculation number, and scores for MTH201, CSC201, INS204, and CSC211.
- GPA is calculated based on the entered scores.
- The new student record is added and saved to students_records.txt.
4. **Data Files**
users.txt: Format for each line: username,password
students_records.txt: Format for each line: name,matricNo,MTH201,CSC201,INS204,CSC211,gpa

**users.txt:** Format for each line: `username,password`
     ``` bash
     admin,adminpass
     user1,userpass1
     ```

 **students_records.txt:** Format for each line: `name,matricNo,MTH201,CSC201,INS204,CSC211,gpa`
     ```bash
     Alice,2021001,85,90,75,80,3.55
     Bob,2021002,80,85,70,75,3.36
     ```


## Notes
- The system ensures that each student has a unique matriculation number.
- Records are sorted by matriculation number before being saved to students_records.txt.
- Make sure the data files (users.txt and students_records.txt) are in the same directory as the executable.
- Future Improvements
- Add more user-friendly error handling and input validation.
- Implement a graphical user interface (GUI) for better user experience.
- Add functionalities to delete student records and update user credentials.

## License
This project is licensed under the MIT License 

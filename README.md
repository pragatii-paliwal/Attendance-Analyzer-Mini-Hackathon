# AttendWise | Attendance Analyzer

A simple, menu-driven attendance management system built in C to help track student attendance, identify defaulters, and calculate how many consecutive classes a student needs to attend to reach a target attendance percentage.

## About the Project

AttendWise is a mini hackathon project designed to make attendance tracking easier and more organized. It provides a simple command-line interface for managing student records, subjects, and attendance reports.

## Features

- **Student Management:** Add and view student records.
- **Subject Management:** Add and view subjects.
- **Attendance Tracking:** Mark students present or absent for each class.
- **Attendance Reports:** View attendance counts and percentages for each student.
- **Defaulter Detection:** Identify students whose attendance falls below 75%.
- **Smart Attendance Calculator:** Calculate how many consecutive classes a student needs to attend to reach a chosen attendance target.
- **File-Based Data Storage:** Store student, subject, and attendance data in text files for future use.

## Built With

- C Programming Language
- Standard C libraries
- File handling
- Structures, arrays, functions, loops, and conditional statements

## Project Structure

```text
AttendWise/
├── main.c
├── students.txt
├── subjects.txt
├── attendance.txt
└── README.md
```

| File | Purpose |
|---|---|
| `main.c` | Contains the program logic and menu |
| `students.txt` | Stores student records |
| `subjects.txt` | Stores subject names |
| `attendance.txt` | Stores attendance data |
| `README.md` | Project documentation |

## Getting Started

### Prerequisites

- A C compiler, such as GCC
- A terminal or code editor, such as VS Code

### Installation and Execution

1. Clone the repository:

   ```bash
   git clone https://github.com/pragatii-paliwal/Attendance-Analyzer-Mini-Hackathon.git
   ```

2. Open the project directory:

   ```bash
   cd Attendance-Analyzer-Mini-Hackathon
   ```

3. Compile the program using GCC:

   ```bash
   gcc main.c -o AttendWise
   ```

4. Run the program on Windows:

   ```powershell
   .\AttendWise.exe
   ```

   On Linux or macOS, run:

   ```bash
   ./AttendWise
   ```

Keep the text data files in the same directory as the executable so the program can access them.

## How to Use

1. Launch AttendWise.
2. Add students and subjects, or use the provided sample data.
3. Mark attendance for each class.
4. Generate attendance reports.
5. Identify students below the 75% attendance threshold.
6. Use the Smart Attendance Calculator to determine the number of consecutive classes required to reach a target percentage.

## Future Improvements

- Track attendance by date and individual class.
- Add student search and record editing.
- Generate more detailed analytics and summaries.
- Improve input validation and error handling.
- Add a graphical user interface.

##DECLARATION & CREDITS

AI tools were used as supportive resources during the development of AttendWise, including assistance with file handling in C, preparation of the PowerPoint presentation, and generation of project flowcharts.

File Handling: AI assistance was used to understand and implement file operations for saving and loading student, subject, and attendance data.

PowerPoint Presentation: AI assistance was used to prepare, organise, and structure the presentation content.

Flowcharts: AI tools were used to generate visual representations of the project's workflow.

Project Development: The team worked on assembling, testing, and reviewing the project.

Declaration: AI was used as an assistance tool during project development. Its contributions are acknowledged transparently.

## Author

**Pragati Paliwal** **590041234**
**Harshit Pathania** **590039195**
**Aditya Chauhan** **590036877**

Developed as a mini hackathon project.

---

*AttendWise: Track attendance. Spot patterns. Plan better.*

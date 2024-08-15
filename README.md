```
      _ _                 
     | (_)                
  ___| |_ _ __   __ _ ___ 
 / __| | | '_ \ / _` / __|
| (__| | | | | | (_| \__ \
 \___|_|_|_| |_|\__, |___/
                 __/ |    
                |___/     

```

# What is clings?
clings is a C version of the popular program "rustlings" made for the Rust programming language.

The purpose of this program is to take you from a total C noob, to somewhere beyond beginner.

![demo](https://raw.githubusercontent.com/danwritecode/clings/master/demo_v3.gif)

# Dependencies
1. gcc
2. make

You can install everything need (on ubuntu) with:
```
sudo apt-get install build-essential
```

# How do I use it?
1. Clone clings to your local machine
2. Open clings in your favorite text editor
3. Open a terminal session
4. Split your screen so you can view them side by side
5. Compile and start clings 
```
make
```
```
./clings
```
6. Start at exercise_01 and continue from there

# Start Script

If you are on a Debian-based distribution, you can use the `start_debian.sh` script to set up your environment. This script will download the repository, install necessary packages, and set up a Tmux split screen for immediate use.

### Instructions:

1. **Download and run the script**:

   ```bash
   sudo wget https://raw.githubusercontent.com/danwritecode/clings/master/start_debian.sh -O start_debian.sh
   sudo chmod +x start_debian.sh
   sudo ./start_debian.sh



# Contributions
The best way to contribute is by helping me create new exercises. I have created an issue for each exercise that needs to be created. The issues follow the flow of "The C Programming Language" book.

To get started, find an exercise you want to work on and create a PR for it. Then refer to The C Programming Language for the specific chapter references in the issue title.

### Exercise Creation Instructions:
1. Create a new directory for the exercise based on the name provided in the issue.
2. Create a readme with an explanation for the user. This should teach them what they need to know without giving the answer.
3. Create 1 or more ".c" exercise files. The file(s) should either fail to compile, or run, or both.
    - The exercise files should be interactive, they should lead the user to learning the things they need to learn.
    - If multiple exercises are needed to have then build up knowledge, then this is fine.
  
**Note:** The objective is not to directly copy the examples or code in the book. We want to create exercises based on the concepts covered in the chapter. The book is serving as a rough guideline for the exercises. Once we have all the exercises from the book, all contributors will work together to figure out how to consolidate and come up with a final set of exercises as the book can be redundant in some spots.

Feel free to ask questions if you need more details.


### Exercise Directory structure
1. README.md file is required
2. N number of ".c" exercises can be included, the program will work through them dynamically
3. At the top of any exercise, provide vague explanation of the objective of the exercise without giving the answer

# To do
1. Rustlings has the concept of asking for a hint, will eventually look to integrate this

### Note
I did this as a project to help me learn C. The source code is far from perfect. I would gladly accept any code reviews and will work to fix any issues that are submitted.

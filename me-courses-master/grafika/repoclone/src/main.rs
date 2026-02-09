use std::fs::File;
use std::io::BufRead;
use std::io::BufReader;
use std::process::Command;
use std::time::Duration;
use std::thread;

#[derive(Clone, Debug)]
struct Student {
    name: String,
    neptun: String,
    url: String
}

/// Clone all of the available student repositories.
fn clone_all() {
    let students = collect_students();
    let mut faileds: Vec<String> = Vec::new();
    let wait_time = Duration::from_secs(2);
    for student in students {
        let dir_name = calc_dir_name(&student);
        println!("{} ...", dir_name);
        let success = clone_repo(student.clone());
        if success == false {
            println!("-- FAILED !!!");
            faileds.push(dir_name);
        }
        thread::sleep(wait_time);
    }
    println!("Failed cases:");
    println!("{:?}", faileds);
}

/// Collect the data of the students from the TSV file.
fn collect_students() -> Vec<Student> {
    let mut students: Vec<Student> = Vec::new();
    let f = File::open("data/students.tsv").expect("Unable to open file!");
    let mut file = BufReader::new(&f);
    for line in file.lines() {
        let l = line.unwrap();
        let parts: Vec<&str> = l.split("\t").collect();
        if parts.len() == 3 {
            let student = Student {
                name: String::from(parts[0]),
                neptun: String::from(parts[1]),
                url: String::from(parts[2])
            };
            students.push(student);
        } else {
            println!("ERROR {} {}", l, parts.len());
        }
    }           
    return students;
}

/// Calculate the name of the git repository.
fn calc_dir_name(student: &Student) -> String {
    let name = student.name.replace(" ", "_") + "_" + &student.neptun.to_uppercase();
    return name;
}

/// Clone the git repository of the student.
fn clone_repo(student: Student) -> bool {
    let dir_name = calc_dir_name(&student);
    let mut cmd = Command::new("git");
    cmd.current_dir("repos");
    cmd.arg("clone");
    cmd.arg(student.url);
    cmd.arg(dir_name);
    cmd.env("GIT_TERMINAL_PROMPT", "0");

    let result = cmd.output().expect("Error");

    if result.status.success() {
        return true;
    } else {
        return false;
    }
}

fn list_names() {
    let students = collect_students();
    let mut result: Vec<String> = Vec::new();
    for student in students {
        let name = student.neptun.to_uppercase() + " " + &student.name.replace(" ", "_");
        result.push(name);
    }
    result.sort();
    for line in result {
        println!("{}", line);
        println!("======");
        println!("");
    }
}

fn main() {
    list_names();
    // clone_all();
}


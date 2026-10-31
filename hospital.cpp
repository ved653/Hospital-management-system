#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// ==========================================
// HOSPITAL MANAGEMENT SYSTEM - PHASE 3
// ==========================================

struct Patient {
    int id;
    string name, age, gender, phone, address, disease;
};

struct Doctor {
    int id;
    string name, specialization, phone;
    double fee;
};

struct Appointment {
    int id, patientId, doctorId;
    string date, time, status;
};

struct Bill {
    int id, patientId;
    double consultation, medicine, other, total;
    string date;
};

vector<Patient> patients;
vector<Doctor> doctors;
vector<Appointment> appointments;
vector<Bill> bills;

const string PF = "patients.txt";
const string DF = "doctors.txt";
const string AF = "appointments.txt";
const string BF = "bills.txt";

// ==========================================
// INPUT FUNCTIONS
// ==========================================

int readInt(const string& prompt) {
    int value;

    while (true) {
        cout << prompt;

        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid input. Enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double readMoney(const string& prompt) {
    double value;

    while (true) {
        cout << prompt;

        if (cin >> value && value >= 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid amount. Enter a non-negative number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string readText(const string& prompt) {
    string value;

    while (true) {
        cout << prompt;
        getline(cin, value);

        if (value.find('|') == string::npos)
            return value;

        cout << "The | character is not allowed.\n";
    }
}

vector<string> split(const string& line) {
    vector<string> fields;
    string field;
    stringstream ss(line);

    while (getline(ss, field, '|'))
        fields.push_back(field);

    if (!line.empty() && line.back() == '|')
        fields.push_back("");

    return fields;
}

// ==========================================
// FIND RECORDS
// ==========================================

template <typename T>
int findId(const vector<T>& records, int id) {
    for (int i = 0; i < (int)records.size(); i++) {
        if (records[i].id == id)
            return i;
    }

    return -1;
}

int patientIndex(int id) {
    return findId(patients, id);
}

int doctorIndex(int id) {
    return findId(doctors, id);
}

int appointmentIndex(int id) {
    return findId(appointments, id);
}

template <typename T>
int nextId(const vector<T>& records, int start) {
    int id = start;

    for (const T& record : records) {
        if (record.id >= id)
            id = record.id + 1;
    }

    return id;
}

// ==========================================
// LOAD DATA
// ==========================================

void loadPatients() {
    ifstream file(PF);
    string line;

    while (getline(file, line)) {
        vector<string> f = split(line);

        if (f.size() != 7)
            continue;

        try {
            Patient p;
            p.id = stoi(f[0]);
            p.name = f[1];
            p.age = f[2];
            p.gender = f[3];
            p.phone = f[4];
            p.address = f[5];
            p.disease = f[6];

            patients.push_back(p);
        }
        catch (...) {}
    }
}

void loadDoctors() {
    ifstream file(DF);
    string line;

    while (getline(file, line)) {
        vector<string> f = split(line);

        if (f.size() != 5)
            continue;

        try {
            Doctor d;
            d.id = stoi(f[0]);
            d.name = f[1];
            d.specialization = f[2];
            d.phone = f[3];
            d.fee = stod(f[4]);

            doctors.push_back(d);
        }
        catch (...) {}
    }
}

void loadAppointments() {
    ifstream file(AF);
    string line;

    while (getline(file, line)) {
        vector<string> f = split(line);

        if (f.size() != 6)
            continue;

        try {
            Appointment a;
            a.id = stoi(f[0]);
            a.patientId = stoi(f[1]);
            a.doctorId = stoi(f[2]);
            a.date = f[3];
            a.time = f[4];
            a.status = f[5];

            appointments.push_back(a);
        }
        catch (...) {}
    }
}

void loadBills() {
    ifstream file(BF);
    string line;

    while (getline(file, line)) {
        vector<string> f = split(line);

        if (f.size() != 6 && f.size() != 7)
            continue;

        try {
            Bill b;
            b.id = stoi(f[0]);
            b.patientId = stoi(f[1]);
            b.consultation = stod(f[2]);
            b.medicine = stod(f[3]);
            b.other = stod(f[4]);
            b.total = stod(f[5]);
            b.date = (f.size() == 7)
                     ? f[6] : "Not specified";

            bills.push_back(b);
        }
        catch (...) {}
    }
}

// ==========================================
// SAVE DATA
// ==========================================

void savePatients() {
    ofstream file(PF);

    for (const Patient& p : patients) {
        file << p.id << '|'
             << p.name << '|'
             << p.age << '|'
             << p.gender << '|'
             << p.phone << '|'
             << p.address << '|'
             << p.disease << '\n';
    }
}

void saveDoctors() {
    ofstream file(DF);
    file << fixed << setprecision(2);

    for (const Doctor& d : doctors) {
        file << d.id << '|'
             << d.name << '|'
             << d.specialization << '|'
             << d.phone << '|'
             << d.fee << '\n';
    }
}

void saveAppointments() {
    ofstream file(AF);

    for (const Appointment& a : appointments) {
        file << a.id << '|'
             << a.patientId << '|'
             << a.doctorId << '|'
             << a.date << '|'
             << a.time << '|'
             << a.status << '\n';
    }
}

void saveBills() {
    ofstream file(BF);
    file << fixed << setprecision(2);

    for (const Bill& b : bills) {
        file << b.id << '|'
             << b.patientId << '|'
             << b.consultation << '|'
             << b.medicine << '|'
             << b.other << '|'
             << b.total << '|'
             << b.date << '\n';
    }
}

// ==========================================
// PATIENT MANAGEMENT
// ==========================================

void showPatient(const Patient& p) {
    cout << "\nPatient ID : " << p.id
         << "\nName       : " << p.name
         << "\nAge        : " << p.age
         << "\nGender     : " << p.gender
         << "\nPhone      : " << p.phone
         << "\nAddress    : " << p.address
         << "\nComplaint  : " << p.disease << '\n';
}

void listPatients() {
    cout << "\n========== PATIENT RECORDS ==========\n";

    if (patients.empty()) {
        cout << "No patients found.\n";
        return;
    }

    for (const Patient& p : patients)
        showPatient(p);
}

void addPatient() {
    Patient p;
    p.id = nextId(patients, 1001);

    cout << "\n--- REGISTER NEW PATIENT ---\n";
    cout << "Assigned Patient ID: " << p.id << '\n';

    p.name = readText("Name: ");
    p.age = readText("Age: ");
    p.gender = readText("Gender: ");
    p.phone = readText("Phone: ");
    p.address = readText("Address: ");
    p.disease = readText("Illness/complaint: ");

    patients.push_back(p);
    savePatients();

    cout << "Patient registered successfully.\n";
}

void searchPatient() {
    int id = readInt("Enter Patient ID: ");
    int i = patientIndex(id);

    if (i == -1) {
        cout << "Patient not found.\n";
        return;
    }

    showPatient(patients[i]);
}

void updatePatient() {
    int id = readInt("Enter Patient ID to update: ");
    int i = patientIndex(id);

    if (i == -1) {
        cout << "Patient not found.\n";
        return;
    }

    Patient& p = patients[i];

    cout << "Enter updated details:\n";
    p.name = readText("Name: ");
    p.age = readText("Age: ");
    p.gender = readText("Gender: ");
    p.phone = readText("Phone: ");
    p.address = readText("Address: ");
    p.disease = readText("Complaint: ");

    savePatients();
    cout << "Patient updated successfully.\n";
}

void deletePatient() {
    int id = readInt("Enter Patient ID to delete: ");
    int i = patientIndex(id);

    if (i == -1) {
        cout << "Patient not found.\n";
        return;
    }

    for (const Appointment& a : appointments) {
        if (a.patientId == id) {
            cout << "Cannot delete: appointment records exist.\n";
            return;
        }
    }

    for (const Bill& b : bills) {
        if (b.patientId == id) {
            cout << "Cannot delete: billing records exist.\n";
            return;
        }
    }

    patients.erase(patients.begin() + i);
    savePatients();

    cout << "Patient deleted successfully.\n";
}

void patientMenu() {
    int choice;

    do {
        cout << "\n========== PATIENT MANAGEMENT ==========\n"
             << "1. Register Patient\n"
             << "2. View All Patients\n"
             << "3. Search Patient\n"
             << "4. Update Patient\n"
             << "5. Delete Patient\n"
             << "0. Back to Main Menu\n";

        choice = readInt("Enter choice: ");

        switch (choice) {
            case 1: addPatient(); break;
            case 2: listPatients(); break;
            case 3: searchPatient(); break;
            case 4: updatePatient(); break;
            case 5: deletePatient(); break;
            case 0: break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}

// ==========================================
// DOCTOR MANAGEMENT
// ==========================================

void showDoctor(const Doctor& d) {
    cout << fixed << setprecision(2)
         << "\nDoctor ID      : " << d.id
         << "\nName           : " << d.name
         << "\nSpecialization : " << d.specialization
         << "\nPhone          : " << d.phone
         << "\nConsultation   : Rs. " << d.fee << '\n';
}

void listDoctors() {
    cout << "\n========== DOCTOR RECORDS ==========\n";

    if (doctors.empty()) {
        cout << "No doctors found.\n";
        return;
    }

    for (const Doctor& d : doctors)
        showDoctor(d);
}

void addDoctor() {
    Doctor d;
    d.id = nextId(doctors, 201);

    cout << "\n--- ADD DOCTOR ---\n";
    cout << "Assigned Doctor ID: " << d.id << '\n';

    d.name = readText("Name: ");
    d.specialization = readText("Specialization: ");
    d.phone = readText("Phone: ");
    d.fee = readMoney("Consultation fee (Rs.): ");

    doctors.push_back(d);
    saveDoctors();

    cout << "Doctor added successfully.\n";
}

void searchDoctor() {
    int id = readInt("Enter Doctor ID: ");
    int i = doctorIndex(id);

    if (i == -1) {
        cout << "Doctor not found.\n";
        return;
    }

    showDoctor(doctors[i]);
}

void updateDoctor() {
    int id = readInt("Enter Doctor ID to update: ");
    int i = doctorIndex(id);

    if (i == -1) {
        cout << "Doctor not found.\n";
        return;
    }

    Doctor& d = doctors[i];

    d.name = readText("Name: ");
    d.specialization = readText("Specialization: ");
    d.phone = readText("Phone: ");
    d.fee = readMoney("Consultation fee: ");

    saveDoctors();
    cout << "Doctor updated successfully.\n";
}

void deleteDoctor() {
    int id = readInt("Enter Doctor ID to delete: ");
    int i = doctorIndex(id);

    if (i == -1) {
        cout << "Doctor not found.\n";
        return;
    }

    for (const Appointment& a : appointments) {
        if (a.doctorId == id) {
            cout << "Cannot delete: appointment records exist.\n";
            return;
        }
    }

    doctors.erase(doctors.begin() + i);
    saveDoctors();

    cout << "Doctor deleted successfully.\n";
}

void doctorMenu() {
    int choice;

    do {
        cout << "\n========== DOCTOR MANAGEMENT ==========\n"
             << "1. Add Doctor\n"
             << "2. View All Doctors\n"
             << "3. Search Doctor\n"
             << "4. Update Doctor\n"
             << "5. Delete Doctor\n"
             << "0. Back to Main Menu\n";

        choice = readInt("Enter choice: ");

        switch (choice) {
            case 1: addDoctor(); break;
            case 2: listDoctors(); break;
            case 3: searchDoctor(); break;
            case 4: updateDoctor(); break;
            case 5: deleteDoctor(); break;
            case 0: break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}

// ==========================================
// APPOINTMENT MANAGEMENT
// ==========================================

void listAppointments() {
    cout << "\n========== APPOINTMENTS ==========\n";

    if (appointments.empty()) {
        cout << "No appointments found.\n";
        return;
    }

    for (const Appointment& a : appointments) {
        int pi = patientIndex(a.patientId);
        int di = doctorIndex(a.doctorId);

        cout << "\nAppointment ID: " << a.id
             << "\nPatient: "
             << (pi == -1 ? "Unknown" : patients[pi].name)
             << " (ID " << a.patientId << ")"
             << "\nDoctor: "
             << (di == -1 ? "Unknown" : doctors[di].name)
             << " (ID " << a.doctorId << ")"
             << "\nDate: " << a.date
             << "\nTime: " << a.time
             << "\nStatus: " << a.status << '\n';
    }
}

void bookAppointment() {
    if (patients.empty() || doctors.empty()) {
        cout << "Add a patient and a doctor first.\n";
        return;
    }

    listPatients();

    int pid = readInt("Enter Patient ID: ");

    if (patientIndex(pid) == -1) {
        cout << "Invalid Patient ID.\n";
        return;
    }

    listDoctors();

    int did = readInt("Enter Doctor ID: ");

    if (doctorIndex(did) == -1) {
        cout << "Invalid Doctor ID.\n";
        return;
    }

    Appointment a;
    a.id = nextId(appointments, 3001);
    a.patientId = pid;
    a.doctorId = did;
    a.date = readText("Appointment date (DD-MM-YYYY): ");
    a.time = readText("Appointment time: ");
    a.status = "Booked";

    appointments.push_back(a);
    saveAppointments();

    cout << "Appointment booked successfully.\n"
         << "Appointment ID: " << a.id << '\n';
}

void cancelAppointment() {
    int id = readInt("Enter Appointment ID to cancel: ");
    int i = appointmentIndex(id);

    if (i == -1) {
        cout << "Appointment not found.\n";
        return;
    }

    if (appointments[i].status == "Cancelled") {
        cout << "Appointment already cancelled.\n";
        return;
    }

    appointments[i].status = "Cancelled";
    saveAppointments();

    cout << "Appointment cancelled successfully.\n";
}

void appointmentMenu() {
    int choice;

    do {
        cout << "\n========== APPOINTMENT MANAGEMENT ==========\n"
             << "1. Book Appointment\n"
             << "2. View Appointments\n"
             << "3. Cancel Appointment\n"
             << "0. Back to Main Menu\n";

        choice = readInt("Enter choice: ");

        switch (choice) {
            case 1: bookAppointment(); break;
            case 2: listAppointments(); break;
            case 3: cancelAppointment(); break;
            case 0: break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}

// ==========================================
// BILLING MANAGEMENT
// ==========================================

void printBill(const Bill& b) {
    int i = patientIndex(b.patientId);

    cout << fixed << setprecision(2)
         << "\n========== HOSPITAL BILL ==========\n"
         << "Bill ID       : " << b.id
         << "\nPatient       : "
         << (i == -1 ? "Unknown" : patients[i].name)
         << "\nPatient ID    : " << b.patientId
         << "\nDate          : " << b.date
         << "\nConsultation  : Rs. " << b.consultation
         << "\nMedicine      : Rs. " << b.medicine
         << "\nOther charges : Rs. " << b.other
         << "\n-----------------------------------"
         << "\nTOTAL         : Rs. " << b.total
         << "\n===================================\n";
}

void generateBill() {
    if (patients.empty()) {
        cout << "Register a patient first.\n";
        return;
    }

    listPatients();

    int pid = readInt("Enter Patient ID: ");

    if (patientIndex(pid) == -1) {
        cout << "Patient not found.\n";
        return;
    }

    Bill b;
    b.id = nextId(bills, 4001);
    b.patientId = pid;

    cout << "\n--- ENTER BILLING DETAILS ---\n";

    b.consultation = readMoney("Consultation charge: ");
    b.medicine = readMoney("Medicine charge: ");
    b.other = readMoney("Other charges: ");

    b.total = b.consultation + b.medicine + b.other;
    b.date = readText("Billing date (DD-MM-YYYY): ");

    bills.push_back(b);
    saveBills();

    printBill(b);
}

void listBills() {
    cout << "\n========== BILL RECORDS ==========\n";

    if (bills.empty()) {
        cout << "No bills found.\n";
        return;
    }

    for (const Bill& b : bills)
        printBill(b);
}

void searchBill() {
    int id = readInt("Enter Bill ID: ");

    for (const Bill& b : bills) {
        if (b.id == id) {
            printBill(b);
            return;
        }
    }

    cout << "Bill not found.\n";
}

void billingMenu() {
    int choice;

    do {
        cout << "\n========== BILLING MANAGEMENT ==========\n"
             << "1. Generate Bill\n"
             << "2. View All Bills\n"
             << "3. Search Bill\n"
             << "0. Back to Main Menu\n";

        choice = readInt("Enter choice: ");

        switch (choice) {
            case 1: generateBill(); break;
            case 2: listBills(); break;
            case 3: searchBill(); break;
            case 0: break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}

// ==========================================
// MAIN FUNCTION
// ==========================================

int main() {
    loadPatients();
    loadDoctors();
    loadAppointments();
    loadBills();

    int choice;

    do {
        cout << "\n========================================\n"
             << "       HOSPITAL MANAGEMENT SYSTEM\n"
             << "========================================\n"
             << "1. Patient Management\n"
             << "2. Doctor Management\n"
             << "3. Appointment Management\n"
             << "4. Billing Management\n"
             << "0. Exit\n"
             << "========================================\n";

        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1:
                patientMenu();
                break;

            case 2:
                doctorMenu();
                break;

            case 3:
                appointmentMenu();
                break;

            case 4:
                billingMenu();
                break;

            case 0:
                savePatients();
                saveDoctors();
                saveAppointments();
                saveBills();

                cout << "Data saved. Thank you!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
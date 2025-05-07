employees = []

# Define the performance qualities with their weights
performance_qualities = {
    "Punctuality": 0.2,
    "Communication": 0.15,
    "Teamwork": 0.2,
    "Problem Solving": 0.2,
    "Initiative": 0.15,
    "Technical Knowledge": 0.1
}

def generate_emp_id():
    return f"E{len(employees) + 1:03d}"

def show_menu():
    print("\n=== Employee Management Expert System ===")
    print("1. Add New Employee")
    print("2. View All Employees")
    print("3. Search Employee by ID")
    print("4. Update Employee Performance")
    print("5. View Performance Summary")
    print("6. HR Knowledge Base")
    print("7. Exit")

def add_employee():
    print("\n--- Add New Employee ---")
    name = input("Enter full name: ")
    dept = input("Enter department (e.g., IT, HR, Sales): ")
    role = input("Enter job role: ")
    doj = input("Enter date of joining (DD/MM/YYYY): ")

    performance = {quality: None for quality in performance_qualities}

    emp = {
        "ID": generate_emp_id(),
        "Name": name,
        "Department": dept,
        "Role": role,
        "DOJ": doj,
        "Performance": performance
    }

    employees.append(emp)
    print(f"Employee added successfully. Employee ID: {emp['ID']}")

def view_all_employees():
    print("\n--- All Employees ---")
    for e in employees:
        print(f"\nID: {e['ID']}")
        print(f"Name: {e['Name']}")
        print(f"Department: {e['Department']}")
        print(f"Role: {e['Role']}")
        print(f"Date of Joining: {e['DOJ']}")
        print(f"Performance:")
        for quality, score in e["Performance"].items():
            print(f"  {quality}: {score}")

def search_employee():
    print("\n--- Search Employee by ID ---")
    eid = input("Enter Employee ID: ")
    for e in employees:
        if e["ID"] == eid:
            print(f"\nID: {e['ID']}")
            print(f"Name: {e['Name']}")
            print(f"Department: {e['Department']}")
            print(f"Role: {e['Role']}")
            print(f"Date of Joining: {e['DOJ']}")
            print(f"Performance:")
            for quality, score in e["Performance"].items():
                print(f"  {quality}: {score}")
            return
    print("Employee not found.")

def update_performance():
    print("\n--- Update Performance ---")
    eid = input("Enter Employee ID: ")
    for e in employees:
        if e["ID"] == eid:
            print("Enter performance ratings (1-10):")
            for quality in performance_qualities:
                score = input(f"{quality}: ")
                e["Performance"][quality] = int(score)
            print("Performance updated successfully.")
            return
    print("Employee not found.")

def calculate_weighted_avg(performance):
    total_score = 0
    total_weight = 0
    for quality, score in performance.items():
        weight = performance_qualities[quality]
        total_score += score * weight
        total_weight += weight
    return total_score / total_weight if total_weight != 0 else 0

def view_performance_summary():
    print("\n--- Employee Performance Summary ---")
    for e in employees:
        scores = list(e["Performance"].values())
        if None not in scores:
            weighted_avg = calculate_weighted_avg(e["Performance"])
            grade = ""
            if weighted_avg >= 9:
                grade = "Outstanding"
            elif weighted_avg >= 7:
                grade = "Excellent"
            elif weighted_avg >= 5:
                grade = "Satisfactory"
            else:
                grade = "Needs Improvement"
            print(f"\n{e['Name']} ({e['ID']}) - Avg: {weighted_avg:.2f} | Grade: {grade}")
        else:
            print(f"\n{e['Name']} ({e['ID']}) - Performance data incomplete")

def hr_knowledge_base():
    print("\n--- HR Knowledge Base ---")
    query = input("Enter HR keyword (leave, bonus, late, policy): ").lower()
    
    if "leave" in query:
        print("Suggestion: Employees can apply for up to 18 paid leaves per year via the HR portal.")
    elif "bonus" in query:
        print("Suggestion: Bonuses are performance-based and disbursed in Q4 each year.")
    elif "late" in query or "attendance" in query:
        print("Suggestion: More than 3 late logins in a month may affect performance review.")
    elif "policy" in query:
        print("Suggestion: Refer to the company intranet > HR > Policy Documents.")
    else:
        print("No suggestion found. Please contact HR.")

def main():
    while True:
        show_menu()
        choice = input("Enter your choice: ")

        if choice == '1':
            add_employee()
        elif choice == '2':
            view_all_employees()
        elif choice == '3':
            search_employee()
        elif choice == '4':
            update_performance()
        elif choice == '5':
            view_performance_summary()
        elif choice == '6':
            hr_knowledge_base()
        elif choice == '7':
            print("Exiting Employee Expert System...")
            break
        else:
            print("Invalid choice. Try again.")

main()

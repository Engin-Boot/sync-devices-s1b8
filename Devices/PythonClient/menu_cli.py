import settings


class MenuCLI:
    @staticmethod
    def displayMainMenu():
        print("1. Add Patient")
        print("2. Edit Patient")
        print("3. Start Procedure")
        print("4. View Patient Details")
        print("5. View Patient Count")
        print("6. Exit")

    @staticmethod
    def displayEditMenu():
        print("1. Edit Name")
        print("2. Edit Age")
        print("3. Edit Gender")
        print("4. Edit Procedure Name")
        print("5. Edit All")

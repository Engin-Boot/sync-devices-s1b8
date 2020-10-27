class Patient:
    def __init__(self, name="", age=0, gender="", procedureName=""):
        self.id = 0
        self.name = name
        self.age = age
        self.gender = gender
        self.procedureName = procedureName
        self.consumables = ""
        self.reportIds = ""
        self.busy = 0

    def setId(self, id):
        self.id = id

    def setName(self, name):
        self.name = name

    def setAge(self, age):
        self.age = age

    def setGender(self, gender):
        self.gender = gender

    def setProcedureName(self, procedureName):
        self.procedureName = procedureName

    def setConsumables(self, consumables):
        self.consumables = consumables

    def setReportIds(self, reportIds):
        self.reportIds = reportIds

    def addConsumables(self, consumables):
        if self.consumables == "":
            self.consumables = consumables
        else:
            self.consumables = self.consumables + "," + consumables

    def addReportIds(self, reportIds):
        if self.reportIds == "":
            self.reportIds = reportIds
        else:
            self.reportIds = self.reportIds + "," + reportIds

    def setBusyStatus(self, busyStatus):
        self.busy = busyStatus

    def getId(self):
        return self.id

    def getName(self):
        return self.name

    def getAge(self):
        return self.age

    def getGender(self):
        return self.gender

    def getProcedureName(self):
        return self.procedureName

    def getConsumables(self):
        return self.consumables

    def getReportIds(self):
        return self.reportIds

    def getBusyStatus(self):
        return self.busy

    def __eq__(self, other):
        self.id = other.getId()
        self.name = other.getName()
        self.age = other.getAge()
        self.gender = other.getGender()
        self.procedureName = other.getProcedureName()
        self.consumables = other.getConsumables()
        self.reportIds = other.getReportIds()
        self.busy = other.getBusyStatus()

    def toString(self):
        return str(self.id) + ";" + self.name + ";" + self.gender + ";" + str(self.age) + ";" + self.procedureName + ";" + self.consumables + ";" + self.reportIds + ";" + str(self.busy)

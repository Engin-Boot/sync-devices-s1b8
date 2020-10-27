import json

class InventoryManager:
    def __init__(self,inventory_filepath):
        self.inventory_filepath = inventory_filepath
        with open(inventory_filepath, 'r') as file:
            self.data = json.load(file)

    def updateInventory(self, procedure):
        for consumable, details in self.data.items():
            if procedure.lower().strip() in details.get("procedure"):
                print(self.data[consumable]["quantity"])
    
    def getScarcityDetails(self):
        scarce_items = []
        for consumable, details in self.data.items():
            quantity = int(details.get("quantity"))
            threshold = int(details.get("threshold"))
            if quantity <= threshold:
                scarce_items.append(f"{consumable}: {quantity}")        
        return scarce_items


import json

class InventoryManager:
    def __init__(self,inventory_filepath):
        self.inventory_filepath = inventory_filepath
        with open(inventory_filepath, 'r') as file:
            self.data = json.load(file)


    def __updateQuantity(self, consumable):
            updated_quantity = int(self.data[consumable]["quantity"]) - 1
            self.data[consumable]["quantity"] = updated_quantity

    def updateInventory(self, procedure):
        for consumable, details in self.data.items():
            procedures = details.get("procedures")
            if procedure.lower().strip() in details.get("procedures"):
                self.__updateQuantity(consumable)
        
        with open(self.inventory_filepath, 'w') as file:
            json.dump(self.data, file)
    

    def getScarcityDetails(self):
        scarce_items = []
        for consumable, details in self.data.items():
            quantity = int(details.get("quantity"))
            threshold = int(details.get("threshold"))
            if quantity <= threshold:
                scarce_items.append(f"{consumable}: {quantity}")        
        return scarce_items
    
// JavaScript program for framework.html


function activateButtons() {
	let saveButton = document.getElementById('Save');

	saveButton.addEventListener('click', function(event) {
	    insertRecord();
	});

	let clearButton = document.getElementById('Clear');

	clearButton.addEventListener('click', function(event) {
		clearTextBoxes();
	});
}


function clearTextBoxes() {
	for (var i = 0; i < textBoxes.length; i++)
    {
    	textBoxes[i].value = "";
    }
    textBoxes[0].disabled = false;
    document.getElementById("Save").textContent = "Save";
}


function editRecord(button) {
	let row = button.parentNode.parentNode;

	for (var i = 0; i < textBoxes.length; i++)
    {
    	textBoxes[i].value = row.cells[i].textContent;
    }
    textBoxes[0].disabled = true;
    document.getElementById("Save").textContent = "Update";
}


async function deleteRecord(button) {
	let row = button.parentNode.parentNode;
	var primaryKey = fields[0];
	var primaryKeyValue = row.cells[0].textContent;

	if (confirm("Are you sure you want to delete record with " + primaryKey + " " + primaryKeyValue + "?")) {
		const url = "deleteRecord.jsp?primaryKey=" + primaryKey + "&primaryKeyValue=" + primaryKeyValue;
		const response = await fetch(url);
		const data = await response.text();

		if (data.includes("Deleted!")) {
			alert("Record with " + primaryKey + " " + primaryKeyValue +" deleted successfully!");
			row.remove();
		} else {
			alert(data);
		}
	} else {
		alert("Delete operation cancelled!");
	}
}


async function insertRow() {
	var whereClause = fields[0] + "='" + textBoxes[0].value + "'";

	const response = await fetch("showAllrecords.jsp?where=" + whereClause);
	const records = await response.json();

	var newRow = await createRow(records[0]);

	var tableBody = document.getElementById("tbody");
	tableBody.appendChild(newRow);
}

function updateRow(values) {
	var table = document.getElementById("table");
	var rows = table.getElementsByTagName("tr");

	for (var i = 1; i < rows.length; i++) { 
        var row = rows[i];
        var cells = row.getElementsByTagName("td");
        if (cells[0].innerHTML === values[0]) { 
            for (var j = 1; j < fieldsCount; j++) {
            	cells[j].innerHTML = values[j];
            }
            break; 
        }
    }
}

async function insertRecord() {
	let values = new Array();

	for (var i = 0; i < textBoxes.length; i++)
    {
		values.push(textBoxes[i].value);

    }

	const url = "insertRecord.jsp?values=" + values;
	const response = await fetch(url);
	const data = await response.text();

	console.log(data);

	const buttonText = document.getElementById("Save").textContent;
	var successPromtWord = null;
	if (buttonText === "Save") {
		successPromtWord = "added";

	} else {
		successPromtWord = "updated"
	}

	if (data.includes("Success!")) {
		alert("Record " + successPromtWord + " successfully!");
		if (successPromtWord === "added") {
			insertRow();
		} else {
			updateRow(values);
		}
	} else {
		alert("Failed to insert record!");
	}

	clearTextBoxes();
}


async function loadTableDetails() {
	const response = await fetch("tableDetails.jsp");
	const data = await response.json();

	tableName = data.tableName;
	fields = data.fields;
	fieldsCount = data.fieldsCount;
}


async function loadTextBoxes() {
	var textBoxesScope = document.getElementById("textBoxes"); 

	fields.forEach(function(field) {
		var textBox = document.createElement("input");
		textBox.type = "text";
		textBox.id = field;
		textBox.name = field;
		textBox.placeholder = "Enter " + field; 

		textBoxesScope.appendChild(textBox);
	});

	textBoxes = document.getElementsByTagName("input");
}


async function loadButtons() {
	var buttonsScope = document.getElementById("buttonsDiv");

	var buttons = ["Save", "Clear"];

	buttons.forEach(function(buttonName) {
		var button = document.createElement("button");
		button.id = buttonName;
		button.name = buttonName;
		button.textContent = buttonName;
		button.className = buttonName;

		buttonsScope.appendChild(button);
	});
	activateButtons();
}


async function createRow(record) {
	var row = document.createElement("tr");
	headers.forEach(function(header) {
		var cell = document.createElement("td");
		if (header === "Actions") {
		    cell.innerHTML = record[header];
		    console.log(cell.innerHTML);
		} else {
		    cell.textContent = record[header];
		    console.log(cell.textContent);
		}
		row.appendChild(cell);
	});
	console.log(row.innerHTML);
	return row;
}


async function createTable(records) {
	var table = document.createElement("table");
	table.id = "table";
	table.name = "table";
	table.border = "2";

	headers = Object.keys(records[0]);

	console.log(headers);
	console.log(fields);

	var thead = document.createElement("thead");
    var headerRow = document.createElement("tr");
    headers.forEach(function(headerText) {
        var headerCell = document.createElement("th");
        headerCell.textContent = headerText;
        headerRow.appendChild(headerCell);
    });
    thead.appendChild(headerRow);
    table.appendChild(thead);

    var tbody = document.createElement("tbody");
    tbody.id = "tbody";
    tbody.name = "tbody";
    records.forEach(async function(record) {
    	var newRow = await createRow(record);
    	console.log(newRow);
        tbody.appendChild(newRow);
    });
    table.appendChild(tbody);

    return table;
}


async function loadTable() {
	var tableScope = document.getElementById("tableDiv");

	var whereClause = "1 = 1";

	const response = await fetch("showAllrecords.jsp?where=" + whereClause);
	const records = await response.json();

	var newTable = await createTable(records);
	tableScope.appendChild(newTable);
}


async function loadPage() {
	await loadTableDetails();
	await loadTextBoxes();
	await loadButtons();
	await loadTable();
}
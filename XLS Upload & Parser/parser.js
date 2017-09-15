$(function() {
    $(document).on('change', ':file', function() {
        var input = $(this),
            numFiles = input.get(0).files ? input.get(0).files.length : 1,
            label = input.val().replace(/\\/g, '/').replace(/.*\//, '');
        input.trigger('fileselect', [numFiles, label]);
    });
    $(document).ready(function() {
        $(':file').on('fileselect', function(event, numFiles, label) {
            var input = $(this).parents('.input-group').find(':text'),
                log = numFiles > 1 ? numFiles + ' files selected' : label;
            if(input.length) {
                input.val(log);
            } else {
                if(log) alert(log);
            }
        });
    });
});

var worksheet;

//Get worksheet from a upload input 
//<input id='file' type='file'.... </input>
var file = document.getElementById("file");
function handleFile(e) {
    var files = e.target.files;
    var i, f;
    for(i = 0, f = files[i]; i != files.length; ++i) {
        var reader = new FileReader();
        var name = f.name;
        reader.onload = function(e) {
            var data = e.target.result;
            var workbook = XLSX.read(data, {
                type: 'binary'
            });
            //do stuff with workbook
            transformWorkbook(workbook);
        };
        reader.readAsBinaryString(f);
    }
}
if(file.addEventListener) {
    file.addEventListener("change", handleFile, false);
}

//Get worksheet from a drag and drop div
//<div id='drop'... </div>
var drop = document.getElementById("drop");
function handleDrop(e) {
    e.stopPropagation();
    e.preventDefault();
    var files = e.dataTransfer.files;
    var i, f;
    for(i = 0, f = files[i]; i != files.length; ++i) {
        var reader = new FileReader();
        var name = f.name;
        reader.onload = function(e) {
            var data = e.target.result;
            var workbook = XLSX.read(data, {
                type: 'binary'
            });
            //do stuff with workbook
            transformWorkbook(workbook);
        };
        reader.readAsBinaryString(f);
    }
}
function handleDragover(e) {
    e.stopPropagation();
    e.preventDefault();
    e.dataTransfer.dropEffect = 'copy';
}
if(drop.addEventListener) {
    drop.addEventListener('dragenter', handleDragover, false);
    drop.addEventListener('dragover', handleDragover, false);
    drop.addEventListener('drop', handleDrop, false);
}

//choose which sheet(s) you want data to be extracted from
function transformWorkbook(workbook) {
    //do stuff with workbook

    //assign all worksheets 
    //worksheet = workbook;

    //access different worksheets via names
    //worksheet = workbook.Sheets["NAME"];

    //access different worksheets via an array
    //worksheet = workbook.Sheets[workbook.SheetNames[INDEX]];

    //if excel document only has one sheet(typical), use code below to access sheet
    worksheet = workbook.Sheets[workbook.SheetNames[0]];

    //coverts worksheet to nested array | useful for generating tables 
    convert(worksheet);
}

//converts worksheet to nested array | pass single sheet
//schema = [[0,1,2],[3,4,5],[6,7,8],[9,0]]
// row two, column three = schema[1][2]
function convert(sheet) {
    var result = [];
    var row;
    var rowNum;
    var colNum;
    var range = XLSX.utils.decode_range(sheet['!ref']);
    for(rowNum = range.s.r; rowNum <= range.e.r; rowNum++) {
        row = [];
        for(colNum = range.s.c; colNum <= range.e.c; colNum++) {
            var cell = sheet[XLS.utils.encode_cell({
                r: rowNum,
                c: colNum
            })];
            if(typeof cell === 'undefined') {
                row.push("");
            } else row.push(cell.w);
        }
        result.push(row);
    }

    //do stuff with result | row count = rowNum | column count = colNum
    //previewValues(rowNum, colNum, result);
}

//generates visible table
//<table id='uploadTable'...</table>
function previewValues(a, b, c) {
    var table = document.getElementById("uploadTable");

    if(a != c.length) {
        a = c.length;
    }
    var rowCount = a;
    var colCount = b;
    var content = c;

    for(var i = 0; i < rowCount; i++) {
        var row = table.insertRow(0);
        for(var j = 0; j < colCount; j++) {
            row.insertCell(j).innerHTML = (content[i])[j];
        }
    }

    var row = table.insertRow(0);

    //$("#uploadTableInput").removeClass("hidden");
}

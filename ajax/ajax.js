document.addEventListener('DOMContentLoaded', function() {
    var xhr = new XMLHttpRequest();
    xhr.open('GET', 'data.xml', true);
    xhr.onreadystatechange = function() {
        if (xhr.readyState == 4 && xhr.status == 200) {
            var xmlDoc = xhr.responseXML;
            var students = xmlDoc.getElementsByTagName('student');
            var tableBody = document.getElementById('studentsTable').getElementsByTagName('tbody')[0];

            for (var i = 0; i < students.length; i++) {
                var row = tableBody.insertRow(i);
                var nameCell = row.insertCell(0);
                var genderCell = row.insertCell(1);
                var ageCell = row.insertCell(2);
                var residenceCell = row.insertCell(3);
                var schoolCell = row.insertCell(4);

                nameCell.textContent = students[i].getElementsByTagName('name')[0].textContent;
                genderCell.textContent = students[i].getElementsByTagName('gender')[0].textContent;
                ageCell.textContent = students[i].getElementsByTagName('age')[0].textContent;
                residenceCell.textContent = students[i].getElementsByTagName('residence')[0].textContent;
                schoolCell.textContent = students[i].getElementsByTagName('school')[0].textContent;
            }
        }
    };
    xhr.send();
});

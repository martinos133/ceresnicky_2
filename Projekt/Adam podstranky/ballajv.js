//footer formular
function validateForm() {
    var name = document.getElementById('name').value;
    var email = document.getElementById('email').value;
    var bio = document.getElementById('bio').value;
    var gender = document.querySelector('input[name="gender"]:checked');
    var newsletter = document.getElementById('newsletter').checked;

    if (!name.trim()) {
        alert("Prosím, zadajte meno.");
        return false;
    }

    if (!email.trim()) {
        alert("Prosím, zadajte email.");
        return false;
    } else {
        var re = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        if (!re.test(email)) {
            alert("Neplatný email.");
            return false;
        }
    }

    if (!bio.trim()) {
        alert("Prosím, zadajte biografiu.");
        return false;
    }

    if (!gender) {
        alert("Prosím, vyberte pohlavie.");
        return false;
    }

    if (!newsletter) {
        alert("Prosím, potvrďte odber noviniek.");
        return false;
    }

    alert("Formulár je správne vyplnený!");
}

handleSmallScreens()

var modal = document.getElementById("myModal");
var span = document.getElementsByClassName("close")[0];
var prevBtn = document.getElementById("prevBtn");
var nextBtn = document.getElementById("nextBtn");
var slides = document.querySelectorAll('.slide');
var currentIndex = 0;

function openModal(index) {
    var slide = slides[index];
    var img = slide.querySelector('img').src;
    var title = slide.querySelector('h2').innerText;
    var description = slide.querySelector('p').innerText;
    var location = slide.querySelector('.difficulty').innerText;
    var additionalTextId = slide.querySelector('img').getAttribute('data-additional-text');

    document.getElementById('modalImage').src = img;
    document.getElementById('modalTitle').innerText = title;
    document.getElementById('modalDescription').innerText = description;
    document.getElementById('modalLocation').innerText = location;
    document.getElementById(additionalTextId).style.display = 'block';
    modal.style.display = "block";
}

function closeModal() {
    modal.style.display = "none";
    document.querySelectorAll('.additional-text').forEach(function(text) {
        text.style.display = 'none';
    });
}

document.querySelectorAll('.slide').forEach(function(slide, index) {
    slide.addEventListener('click', function() {
        currentIndex = index;
        openModal(currentIndex);
    });
});

prevBtn.onclick = function() {
    currentIndex = (currentIndex > 0) ? currentIndex - 1 : slides.length - 1;
    openModal(currentIndex);
}

nextBtn.onclick = function() {
    currentIndex = (currentIndex < slides.length - 1) ? currentIndex + 1 : 0;
    openModal(currentIndex);
}

span.onclick = closeModal;
window.onclick = function(event) {
    if (event.target == modal) {
        closeModal();
    }
}

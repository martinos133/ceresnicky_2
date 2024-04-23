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

function presunNaHistoriuTatier() {
    const sekcia = document.getElementById('historiaTatier');
    sekcia.scrollIntoView({ behavior: 'smooth' });
}

function presunNaremesla() {
    const sekcia = document.getElementById('remesla');
    sekcia.scrollIntoView({ behavior: 'smooth' });
}

function presunNalomnicky() {
    const sekcia = document.getElementById('lomnicky');
    sekcia.scrollIntoView({ behavior: 'smooth' });
}

function presunNabelianska() {
    const sekcia = document.getElementById('belianska');
    sekcia.scrollIntoView({ behavior: 'smooth' });
}

function presunNapleso() {
    const sekcia = document.getElementById('pleso');
    sekcia.scrollIntoView({ behavior: 'smooth' });
}

function presunNatanap() {
    const sekcia = document.getElementById('tanap');
    sekcia.scrollIntoView({ behavior: 'smooth' });
}

function presunNadrevo() {
    const sekcia = document.getElementById('drevo');
    sekcia.scrollIntoView({ behavior: 'smooth' });
}

function presunNatkanie() {
    const sekcia = document.getElementById('tkanie');
    sekcia.scrollIntoView({ behavior: 'smooth' });
}

function presunNavyroba() {
    const sekcia = document.getElementById('vyroba');
    sekcia.scrollIntoView({ behavior: 'smooth' });
}
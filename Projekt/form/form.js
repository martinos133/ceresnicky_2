document.addEventListener('DOMContentLoaded', function() {
    const form = document.querySelector('form');
    const emailRegex = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,6}$/;

    form.addEventListener('submit', function(event) {
        event.preventDefault();

        const fullName = document.getElementById('fullName').value;
        const username = document.getElementById('username').value;
        const email = document.getElementById('email').value;
        const phoneNumber = document.getElementById('phoneNumber').value;
        const password = document.getElementById('password').value;
        const confirmPassword = document.getElementById('confirmPassword').value;
        const gender = document.querySelector('input[name="gender"]:checked');

        if (!fullName || !username || !email || !phoneNumber || !password || !confirmPassword || !gender) {
            alert('Všetky polia musia byť vyplnené.');
            return;
        }

        if (password !== confirmPassword) {
            alert('Heslá sa musia zhodovať.');
            return;
        }

        if (!emailRegex.test(email)) {
            alert('Emailová adresa je neplatná.');
            return;
        }

        alert('Formulár bol úspešne odoslaný.');
        // Tu môžete pridať ďalšie akcie, napríklad odoslanie dát na server
    });
});

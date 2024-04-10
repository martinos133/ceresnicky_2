

  // Handle closing dropdowns if a user clicked the body
window.addEventListener('mouseup', (event) => {
    if (dropdownIsOpen) {
      dropdowns.forEach((dropdownButton) => {
        let dropdown = document.querySelector(`#${dropdownButton.dataset.dropdown}`)
        let targetIsDropdown = dropdown == event.target
  
        if (dropdownButton == event.target) {
          return
        }
  
        if ((!targetIsDropdown) && (!dropdown.contains(event.target))) {
          dropdown.classList.remove('show')
        }
      })
    }
  })
  
  // Open links in mobiles
  function handleSmallScreens() {
    document.querySelector('.navbar-toggler')
      .addEventListener('click', () => {
        let navbarMenu = document.querySelector('.navbar-menu')
  
        if (!navbarMenu.classList.contains('active')) {
          navbarMenu.classList.add('active')
        } else {
          navbarMenu.classList.remove('active')
        }
      })
  }
  
  handleSmallScreens()

  var modal = document.getElementById("myModal");
var span = document.getElementsByClassName("close")[0];

function openModal(imgSrc, title, description, location, additionalTextId) {
    document.getElementById('modalImage').src = imgSrc;
    document.getElementById('modalTitle').innerText = title;
    document.getElementById('modalDescription').innerText = description;
    document.getElementById('modalLocation').innerText = location;
    // Hide all additional texts
    document.querySelectorAll('.additional-text').forEach(function(text) {
        text.style.display = 'none';
    });
    // Show the specific additional text
    document.getElementById(additionalTextId).style.display = 'block';
    modal.style.display = "block";
}

function closeModal() {
    modal.style.display = "none";
    // Hide all additional texts
    document.querySelectorAll('.additional-text').forEach(function(text) {
        text.style.display = 'none';
    });
}

document.querySelectorAll('.slide').forEach(function(slide) {
    slide.addEventListener('click', function() {
        var img = slide.querySelector('img').src;
        var title = slide.querySelector('h2').innerText;
        var description = slide.querySelector('p').innerText;
        var location = slide.querySelector('.difficulty').innerText;
        var additionalTextId = slide.querySelector('img').getAttribute('data-additional-text');
        openModal(img, title, description, location, additionalTextId);
    });
});

span.onclick = closeModal;
window.onclick = function(event) {
    if (event.target == modal) {
        closeModal();
    }
}

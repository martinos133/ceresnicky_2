

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

// Get the <span> element that closes the modal
var span = document.getElementsByClassName("close")[0];


span.onclick = function() {
    modal.style.display = "none";
}


window.onclick = function(event) {
    if (event.target == modal) {
        modal.style.display = "none";
    }
}

document.querySelectorAll('.slide').forEach(function(slide) {
    slide.addEventListener('click', function() {
        var img = slide.querySelector('img');
        var title = slide.querySelector('h2').innerText;
        var description = slide.querySelector('p').innerText;

        document.getElementById('modalImage').src = img.src;
        document.getElementById('modalTitle').innerText = title;
        document.getElementById('modalDescription').innerText = description;

        modal.style.display = "block";
    });
});
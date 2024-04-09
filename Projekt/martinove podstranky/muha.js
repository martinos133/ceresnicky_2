

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


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
  
  document.getElementById('restaurant-select').addEventListener('change', function() {
    alert('You selected: ' + this.value);
});

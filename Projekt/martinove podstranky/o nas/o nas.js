document.addEventListener('DOMContentLoaded', function() {
    const activitiesMap = document.getElementById('activitiesMap');
    const activities = [
        { name: 'Turistika', description: 'Prechádzka po chodníkoch, výstupy na vrcholy.' },
        { name: 'Horolezectvo', description: 'Horolezecké trasy v oblasti.' },
        { name: 'Kajakovanie', description: 'Potery na riekach vo vysokých Tatrách.' },
        // Pridajte ďalšie aktivity podľa potreby
    ];

    activities.forEach(activity => {
        const activityElement = document.createElement('div');
        activityElement.innerHTML = `<h3>${activity.name}</h3><p>${activity.description}</p>`;
        activitiesMap.appendChild(activityElement);
    });
});

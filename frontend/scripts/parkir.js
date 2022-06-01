const today = new Date();
const dd = String(today.getDate()).padStart(2, "0");
const mm = String(today.getMonth() + 1).padStart(2, "0"); //January is 0!
const yyyy = today.getFullYear();
document.getElementById("dateParkir").max = yyyy + "-" + mm + "-" + dd;
document.getElementById("dateParkir").value = yyyy + "-" + mm + "-" + dd;

const labelParkir = [];
const jmlKendaraan = [];
for (let i = 0; i < 24; i++) {
  let temp = i < 10 ? "0" + i : i;
  labelParkir.push(`${temp}:00`);
  const min = 40;
  const rand = Math.floor(Math.random() * 11);
  jmlKendaraan.push(rand + min);
}

const dataParkir = {
  labels: labelParkir,
  datasets: [
    {
      label: "Jumlah Kendaraan",
      data: jmlKendaraan,
      borderWidth: 2,
      borderColor: blue2,
      backgroundColor: blue3,
      lineTension: 0,
    },
  ],
};

const parkirChart = new Chart("parkirChart", {
  type: "bar",
  data: dataParkir,
  options: {
    legend: {
      display: false,
    },
    scales: {
      xAxes: [
        {
          display: true,
          scaleLabel: {
            display: true,
            labelString: "Waktu",
          },
        },
      ],
      yAxes: [
        {
          display: true,
          scaleLabel: {
            display: true,
            labelString: "Jumlah Kendaraan",
          },
          ticks: {
            beginAtZero: true,
            steps: 10,
            stepValue: 5,
            max: 55,
          },
        },
      ],
    },
    tooltips: {
      callbacks: {
        title: function (tooltipItem, data) {
          return "Pukul " + data.labels[tooltipItem[0].index];
        },
      },
    },
    plugins: {
      datalabels: {
        display: false,
      },
    },
  },
});

async function getDataParkir() {
  const dateParkir = document.getElementById("dateParkir").value;
  if (!dateParkir) {
    alert("Isi tanggal dengan benar");
  } else {
    const date = dateParkir.split("-");
    const link = `localhost:8080/parkir/${date[2]}${date[1]}${date[0]}`;
    let data = await getRequest(link);
    const newJmlKendaraan = [];
    for (let i = 0; i < data.length; i++) {
      newJmlKendaraan.push(!data[i].jumlah ? 0 : data[i].jumlah);
    }
    while (newJmlKendaraan.length < 24) {
      newJmlKendaraan.push(0);
    }
    parkirChart.data.datasets[0].data = newJmlKendaraan;
    parkirChart.update();
  }
}

// getDataParkir();

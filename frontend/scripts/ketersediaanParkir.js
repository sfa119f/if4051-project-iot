const maxPark = 500;
document.getElementById("ketersediaan_parkir").innerHTML = maxPark;

const ketersediaanChart = new Chart("ketersediaanChart", {
  type: "pie",
  data: {
    labels: ["Kosong", "Terisi"],
    datasets: [
      {
        backgroundColor: [orange1, blue2],
        data: [maxPark, 0],
        sumData: maxPark,
        // data: [0, 0, 0, 0, 0],
        // sumData: 0,
      },
    ],
  },
  options: {
    tooltips: {
      callbacks: {
        // title: function (tooltipItem, data) {
        //   return data.labels[tooltipItem[0].index];
        // },
        // label: function (tooltipItem, data) {
        //   return data.datasets[0].data[tooltipItem.index];
        // },
        afterLabel: function (tooltipItem, data) {
          var dataset = data.datasets[0];
          var percent = (
            (dataset.data[tooltipItem.index] / dataset.sumData) *
            100
          ).toFixed(2);
          return "(" + percent + "%)";
        },
      },
    },
    plugins: {
      datalabels: {
        formatter: (value, ctx) => {
          const sumData = ctx.chart.data.datasets[0].sumData;
          let temp = ((value * 100) / sumData).toFixed(2);
          if (temp < 10) return "";
          else return temp + "%";
        },
        color: "#fff",
      },
    },
  },
});

async function updateKetersediaan() {
  const today = new Date();
  const dd = String(today.getDate()).padStart(2, "0");
  const mm = String(today.getMonth() + 1).padStart(2, "0"); //January is 0!
  const yyyy = today.getFullYear();
  const hours = today.getHours();
  const link = `http://localhost:8080/parkir/${dd}${mm}${yyyy}`;
  let data = await getRequest(link);
  ketersediaanChart.data.datasets[0].data = [
    maxPark - data[hours].jumlah,
    data[hours].jumlah,
  ];
  ketersediaanChart.update();
  document.getElementById("ketersediaan_parkir").innerHTML =
    maxPark - data[hours].jumlah;
}

setInterval(updateKetersediaan, 60000);

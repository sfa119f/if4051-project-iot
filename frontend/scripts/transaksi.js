const transaksiChart = new Chart("transaksiChart", {
  type: "pie",
  data: {
    labels: ["< 0.5 jt", "0.5 - 1 jt", "1 - 1.5 jt", "1.5 - 2 jt", "> 2 jt"],
    datasets: [
      {
        backgroundColor: [blue2, blue3, orange1, orange2, orange3],
        data: [5, 4, 3, 2, 1],
        sumData: 15,
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

function getDataTransaksi() {
  const monthTransaksi = document.getElementById("monthTransaksi").value;
  const yearTransaksi = document.getElementById("yearTransaksi").value;
  console.log("monthTransaksi", monthTransaksi);
  console.log("yearTransaksi", yearTransaksi);
  if (!monthTransaksi || !yearTransaksi) {
    alert("Isi bulan dan/atau tahun dengan benar");
  } else {
    const newYValue = [];
    let newSum = 0;
    while (newYValue.length != 5) {
      let temp = Math.floor(Math.random() * 51);
      newYValue.push(temp);
      newSum += temp;
    }
    transaksiChart.data.datasets[0].data = newYValue;
    transaksiChart.data.datasets[0].sumData = newSum;
    transaksiChart.update();
  }
}

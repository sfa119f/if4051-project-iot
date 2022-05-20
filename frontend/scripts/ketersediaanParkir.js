const ketersediaanChart = new Chart("ketersediaanChart", {
  type: "pie",
  data: {
    labels: ["Kosong", "Terisi"],
    datasets: [
      {
        backgroundColor: [orange1, blue2],
        data: [61, 294],
        sumData: 355,
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

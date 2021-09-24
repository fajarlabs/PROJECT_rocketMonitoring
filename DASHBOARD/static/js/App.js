window.data_list = [];

var map = new ol.Map({
  target: 'map',
  layers: [
    new ol.layer.Tile({
      source: new ol.source.OSM()
    })
  ],
  view: new ol.View({
    center: ol.proj.fromLonLat([ 107.68213482329772, -7.661243419310371]),
    zoom: 15
  })
});

var centerLongitudeLatitude = ol.proj.fromLonLat([107.68213482329772, -7.661243419310371]);
var layer = new ol.layer.Vector({
  source: new ol.source.Vector({
    projection: 'EPSG:4326',
    features: [new ol.Feature(new ol.geom.Circle(centerLongitudeLatitude, 300))]
  }),
  style: [
    new ol.style.Style({
      stroke: new ol.style.Stroke({
        color: 'blue',
        width: 3
      }),
      fill: new ol.style.Fill({
        color: 'rgba(0, 0, 255, 0.1)'
      })
    })
  ]
});

map.addLayer(layer);

$(document).ready(function() {            
    $('#nav').CompassRose({pos: 0});

    var last_bearing = 0;
    setInterval(function() {
        var data_list = [];
        window.data_list.forEach(function(row){
            data_list.push({x: row[1]/100, y: row[2]/100, z: row[3]/100, color: '2'});
        });

        function unpack(rows, key) {
            return rows.map(function(row){ 
                return row[key]; 
            }); 
        }

        var x = unpack(data_list,'x');
        var y = unpack(data_list,'y');
        var z = unpack(data_list,'z')
        var c = unpack(data_list,'color');
        
        Plotly.newPlot('app_map', [{
          type: 'scatter3d',
          mode: 'lines',
          x: x,
          y: y,
          z: z,
          opacity: 1,
          line: {
            width: 6,
            color: c,
            reversescale: false
          }
        }], {
          height: 440
        });

    },1000);
    
    // setInterval(function() {
    //     $.get( "/data/last_one", function( json ) {

    //         window.data_list.push(...[json.data]);

    //         var new_bearing = parseInt(json.data[5]);
    //         new_bearing = 22.5 * new_bearing;
    //         if(last_bearing != new_bearing) {
    //             /*
    //             - Getting 16 point Azimuth bearing direction (0 - 15).
    //             - Getting 16 point Azimuth bearing Names (N, NNE, NE, ENE, E, ESE, SE, SSE, S, SSW, SW, WSW, W, WNW, NW, NNW)
    //             */
    //             $('.imgB1').rotate({ angle:last_bearing,animateTo:new_bearing,easing: $.easing.easeInOutExpo });
    //             last_bearing = new_bearing;
    //         }

    //         $('#tms').html('').html(json.data[18]);
    //         $('#x').html('').html(json.data[1]);
    //         $('#y').html('').html(json.data[2]);
    //         $('#z').html('').html(json.data[3]);
    //         $('#azimuth').html('').html(json.data[4]);
    //         $('#bearing').html('').html(json.data[5]);
    //         $('#direction').html('').html(json.data[6]);
    //         $('#temperature').html('').html(json.data[7]);
    //         $('#pressure').html('').html(json.data[8]);
    //         $('#altitude').html('').html(json.data[9]);
    //         $('#gps_latitude').html('').html(json.data[10]);
    //         $('#gps_longitude').html('').html(json.data[11]);
    //         $('#gps_age').html('').html(json.data[12]);
    //         $('#gps_altitude').html('').html(json.data[13]);
    //         $('#gps_sat').html('').html(json.data[14]);
    //         $('#gps_course').html('').html(json.data[15]);
    //         $('#gps_speed').html('').html(json.data[16]);
    //         $('#rssi').html('').html(json.data[17]);

            
    //     });
    // },333);
});

Highcharts.theme = {
    colors: ['#2b908f', '#90ee7e', '#f45b5b', '#7798BF', '#aaeeee', '#ff0066',
        '#eeaaee', '#55BF3B', '#DF5353', '#7798BF', '#aaeeee'],
    chart: {
        backgroundColor: {
            linearGradient: { x1: 0, y1: 0, x2: 1, y2: 1 },
            stops: [
                [0, '#2a2a2b'],
                [1, '#3e3e40']
            ]
        },
        style: {
            fontFamily: '\'Unica One\', sans-serif'
        },
        plotBorderColor: '#606063'
    },
    title: {
        style: {
            color: '#E0E0E3',
            textTransform: 'uppercase',
            fontSize: '20px'
        }
    },
    subtitle: {
        style: {
            color: '#E0E0E3',
            textTransform: 'uppercase'
        }
    },
    xAxis: {
        gridLineColor: '#707073',
        labels: {
            style: {
                color: '#E0E0E3'
            }
        },
        lineColor: '#707073',
        minorGridLineColor: '#505053',
        tickColor: '#707073',
        title: {
            style: {
                color: '#A0A0A3'
            }
        }
    },
    yAxis: {
        gridLineColor: '#707073',
        labels: {
            style: {
                color: '#E0E0E3'
            }
        },
        lineColor: '#707073',
        minorGridLineColor: '#505053',
        tickColor: '#707073',
        tickWidth: 1,
        title: {
            style: {
                color: '#A0A0A3'
            }
        }
    },
    tooltip: {
        backgroundColor: 'rgba(0, 0, 0, 0.85)',
        style: {
            color: '#F0F0F0'
        }
    },
    plotOptions: {
        series: {
            dataLabels: {
                color: '#F0F0F3',
                style: {
                    fontSize: '13px'
                }
            },
            marker: {
                lineColor: '#333'
            }
        },
        boxplot: {
            fillColor: '#505053'
        },
        candlestick: {
            lineColor: 'white'
        },
        errorbar: {
            color: 'white'
        }
    },
    legend: {
        backgroundColor: 'rgba(0, 0, 0, 0.5)',
        itemStyle: {
            color: '#E0E0E3'
        },
        itemHoverStyle: {
            color: '#FFF'
        },
        itemHiddenStyle: {
            color: '#606063'
        },
        title: {
            style: {
                color: '#C0C0C0'
            }
        }
    },
    credits: {
        style: {
            color: '#666'
        }
    },
    labels: {
        style: {
            color: '#707073'
        }
    },
    drilldown: {
        activeAxisLabelStyle: {
            color: '#F0F0F3'
        },
        activeDataLabelStyle: {
            color: '#F0F0F3'
        }
    },
    navigation: {
        buttonOptions: {
            symbolStroke: '#DDDDDD',
            theme: {
                fill: '#505053'
            }
        }
    },
    // scroll charts
    rangeSelector: {
        buttonTheme: {
            fill: '#505053',
            stroke: '#000000',
            style: {
                color: '#CCC'
            },
            states: {
                hover: {
                    fill: '#707073',
                    stroke: '#000000',
                    style: {
                        color: 'white'
                    }
                },
                select: {
                    fill: '#000003',
                    stroke: '#000000',
                    style: {
                        color: 'white'
                    }
                }
            }
        },
        inputBoxBorderColor: '#505053',
        inputStyle: {
            backgroundColor: '#333',
            color: 'silver'
        },
        labelStyle: {
            color: 'silver'
        }
    },
    navigator: {
        handles: {
            backgroundColor: '#666',
            borderColor: '#AAA'
        },
        outlineColor: '#CCC',
        maskFill: 'rgba(255,255,255,0.1)',
        series: {
            color: '#7798BF',
            lineColor: '#A6C7ED'
        },
        xAxis: {
            gridLineColor: '#505053'
        }
    },
    scrollbar: {
        barBackgroundColor: '#808083',
        barBorderColor: '#808083',
        buttonArrowColor: '#CCC',
        buttonBackgroundColor: '#606063',
        buttonBorderColor: '#606063',
        rifleColor: '#FFF',
        trackBackgroundColor: '#404043',
        trackBorderColor: '#404043'
    }
};
// Apply the theme
Highcharts.setOptions(Highcharts.theme);


var data_list = [];
var dt_series = [];

    window.data_list.forEach(function(row){
        data_list.push({temperature: row[7], altitude: row[9], speed: row[16], color: '2'});
    });

    function unpack(rows, key) {
        return rows.map(function(row){ 
            return row[key]; 
        }); 
    }

    dt_series.push({
        name: 'Altitude',
        data: (function () {
        // generate an array of random data
        var data = [],
            time = (new Date()).getTime(),
            i;

        for (i = -19; i <= 0; i += 1) {
            data.push({
                x: time + i * 1000,
                y: Math.random()
            });
        }
        return data;
        }())
    });

    dt_series.push({
        name: 'Temperature',
        data: (function () {
        // generate an array of random data
        var data = [],
            time = (new Date()).getTime(),
            i;

        for (i = -19; i <= 0; i += 1) {
            data.push({
                x: time + i * 1000,
                y: Math.random()
            });
        }
        return data;
        }())
    });

Highcharts.chart('chart2', {
    chart: {
        type: 'spline',
        animation: Highcharts.svg, // don't animate in old IE
        marginRight: 10,
        events: {
            load: function () {
                // // set up the updating of the chart each second
                // var series0 = this.series[0];
                // setInterval(function () {
                //     var x = (new Date()).getTime(), // current time
                //         y = Math.random();
                //     series0.addPoint([x, y], true, true);
                // }, 1000);

                // var series1 = this.series[1];
                // setInterval(function () {
                //     var x = (new Date()).getTime(), // current time
                //         y = Math.random();
                //     series1.addPoint([x, y], true, true);
                // }, 1000);
            }
        }
    },

    time: {
        useUTC: false
    },

    title: {
        text: 'Live data'
    },

    accessibility: {
        announceNewData: {
            enabled: true,
            minAnnounceInterval: 15000,
            announcementFormatter: function (allSeries, newSeries, newPoint) {
                if (newPoint) {
                    return 'New point added. Value: ' + newPoint.y;
                }
                return false;
            }
        }
    },

    xAxis: {
        type: 'datetime',
        tickPixelInterval: 150
    },

    yAxis: {
        title: {
            text: 'Value'
        },
        plotLines: [{
            value: 0,
            width: 1,
            color: '#808080'
        }]
    },

    tooltip: {
        headerFormat: '<b>{series.name}</b><br/>',
        pointFormat: '{point.x:%Y-%m-%d %H:%M:%S}<br/>{point.y:.2f}'
    },

    legend: {
        enabled: true
    },

    exporting: {
        enabled: true
    },

    series: dt_series
});
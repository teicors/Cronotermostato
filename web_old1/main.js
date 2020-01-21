<!--
var myarr;

myarr = [
  {
    id: 1,
    startValue: {stringtime1},
    endValue: {stringtime2},
    color: "#CF1920",
    startAt: "00:00",
    endAt: "23:59"
  }, {
    id: 2,
    startValue: {stringtime3},
    endValue: {stringtime4},
    color: "#CF1920",
    startAt: "00:00",
    endAt: "23:59"
  }, {
    id: 3,
    startValue: {stringtime5},
    endValue: {stringtime6},
    color: "#CF1920",
    startAt: "00:00",
    endAt: "23:59"
  }
];
-->

$(function() {
  var renderLabel;
  renderLabel = function(ui, customContent) {
    var content, endAt, range, startAt;
    if (customContent == null) {
      customContent = false;
    }
    range = ui.range;
    startAt = moment(range.startAt, "H:mm").add(range.startValue, "minutes");
    endAt = moment(range.startAt, "H:mm").add(range.endValue, "minutes");
    content = "" + (startAt.format("H:mm")) + " -- " + (endAt.format("H:mm"));
    if (customContent) {
      content = $("<div style='left: -40px;position: absolute;'>" + (startAt.format("H:mm")) + "</div><div style='right: -40px;position: absolute;'>" + (endAt.format("H:mm")) + "</div>");
    }
    return content;
  };
  return $('#slider-range-custom-label').rangeSlider({
    min: 0,
    max: 1440,
    step: 15,
    ranges: myarr,
    rangeLabel: function(event, ui) {
      return ui.label.empty().append(renderLabel(ui, true));
    },
    rangeSlide: function(event, ui) {
      return $("#display-label-timer").empty().append(renderLabel(ui));
    }
  });
});

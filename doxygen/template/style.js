import React, {StyleSheet, Dimensions, PixelRatio} from "react-native";
const {width, height, scale} = Dimensions.get("window"),
    vw = width / 100,
    vh = height / 100,
    vmin = Math.min(vw, vh),
    vmax = Math.max(vw, vh);

export default StyleSheet.create({
    "navbar-brand>img": {
        "display": "inline"
    },
    "page-header": {
        "border": "none",
        "marginTop": 70,
        "marginRight": 0,
        "marginBottom": 20,
        "marginLeft": 0
    },
    "n-hidden": {
        "display": "none"
    },
    "tdmlabels-right": {
        "paddingTop": 10,
        "paddingRight": 10,
        "paddingBottom": 10,
        "paddingLeft": 10
    },
    "memname": {
        "fontSize": 16
    }
});
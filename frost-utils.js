
//syntax: [[element, {attribute: value], ...]
function create_elements(elements, location = "none") {
    for (var element of elements) {
        var created_element = document.createElement(element[0])
        var key; var value;
        let location_ = [false, location]

        for ([key, value] of Object.entries(element[1])) {
            if (key == "text") {
                created_element.appendChild(document.createTextNode(value)); continue}
            else if (key == "location") {
                location_ = [true, value]; continue}

            created_element.setAttribute(key, value)}

        if (location_[0] = true && location_[1] != "none") {
            location_[1].append(created_element); continue}

        location_[1].append(created_element)
    }
}


export {
        create_elements
       }

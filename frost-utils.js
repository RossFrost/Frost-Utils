
//syntax: [[element, {attribute: value], ...]
function CREATE_ELEMENTS(elements, location = "none") {
    for (var element of elements) {
        var createdElement = document.createElement(element[0]) // createElement -> function; not createdElement -> variable
        var key; var value;
        let location_ = [false, location]

        for ([key, value] of Object.entries(element[1])) {
            if (key == "text") {
                createdElement.appendChild(document.createTextNode(value)); continue}
            else if (key == "location") {
                location_ = [true, value]; continue}

            createdElement.setAttribute(key, value)}

        if (location_[0] = true && location_[1] != "none") {
            location_[1].append(createdElement); continue}

        location_[1].append(createdElement)}
}


export {
        CREATE_ELEMENTS
       }

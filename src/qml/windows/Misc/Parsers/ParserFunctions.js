function standartOnClickFunction(dataArr, parserType, parserMode)
{
    // text
    var param = [dataArr[0]]
    var mode  = [parserType, parserMode]
    parsers.apiHandlerStartDownloading(param, mode)
}
function mangadexOnClickFunction(dataArr, parserType, parserMode)
{
    // text; en; ru; other
    var param = [dataArr[0], dataArr[1], dataArr[2], dataArr[3]]
    var mode  = [parserType, parserMode]
    parsers.apiHandlerStartDownloading(param, mode)
}

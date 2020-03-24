function standartOnClickFunction(text, parserType, parserMode)
{
    var param = [text]
    var mode  = [parserType, parserMode]
    //apiHandler.universalStartDownloading(param, mode)
    apiHandler.slotStartDownloding(param, mode)
}
function mangadexOnClickFunction(text, parserType, parserMode, enChecked, ruChecked, otherChecked)
{
    var param = [text, enChecked, ruChecked, otherChecked]
    var mode  = [parserType, parserMode]
    //apiHandler.universalStartDownloading(param, mode)
    apiHandler.slotStartDownloding(param, mode)
}

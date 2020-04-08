function bytesToHumanReadable(bytes)
{
    if (bytes === 0)
        return 0 + " Bit/s"

    var tmp = 0
    if (bytes < 1024)
    {
        tmp = bytes + " Byte/s"
    }
    else
    {
        tmp = (bytes / 1024);
        if (tmp < 1024)
        {
            tmp = Math.round(tmp * 1000) / 1000
            tmp += " Kb/s";
        }
        else
        {
            tmp = tmp / 1024;
            if (tmp < 1024)
            {
                tmp = Math.round(tmp * 1000) / 1000
                tmp += " Mb/s"
            }
            else
            {
                tmp = tmp / 1024;
                tmp = Math.round(tmp * 1000) / 1000
                tmp += " Gb/s"
            }
        }
    }
    return tmp
}

function cutNumberByPercents(number, percents)
{
    return (number / 100) * percents;
}

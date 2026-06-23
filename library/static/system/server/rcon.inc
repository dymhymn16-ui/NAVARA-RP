
callback: CheckRconCommands()
{
    mysql_tquery(sql_connection, "SELECT id, command FROM rcon LIMIT 1", "OnRconCommandFetched", "");
    return 1;
}

callback: OnRconCommandFetched()
{
    new rows, idx, cmds[200];

    rows = cache_num_rows();
    
    if(!rows) return 1;

    for(new i; i < rows; ++i)
	{
        idx = cache_get_field_content_int(i, "id", sql_connection);
        cache_get_field_content(i, "command", cmds, sql_connection, 200);

        SendRconCommand(cmds);
        SendRconCommand("reloadbans");

        RunQuery("DELETE FROM rcon WHERE id = %d", idx);
    }

    return 1;
}
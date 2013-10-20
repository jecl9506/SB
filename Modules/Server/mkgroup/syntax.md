# mkgroup syntax
`mkgroup` is used to create a new group.
If group already exists, the new one replace it.


## Usage: mkgroup "group_name" "attributs"
`group_name` is the name of the group you want to create.
This argument is mandatory.

`"attributs"` are the group's attributs.
The synatx is the following:
- `+<type>:<value>` : Include all clients with these values.
- `-<type>:<value>` : Exclude all clients with these values.
Availables types and values:
- `os_type`    : `windows`, `unix`, `?`
- `os_version` : string
- `os_arch`    : `32`, `64`, `?`
- `jobs`       : integer
- `version`	   : integer

Attributs are mandatory: at least one attribut must be specified.
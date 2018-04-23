open Utils;
let styles = requireCSSModule("src/ListItem.module.css");
let cn = (name) => className(styles, name);

let component = ReasonReact.statelessComponent("ListItem");
let make = (~index, ~story, _children) => {
  let  {url, title, points, comments_count, id, user, time_ago} : HackerNews.story = story;
  let comments_plural = switch comments_count {
    | 1 => ""
    | _ => "s"
  };
  let points_plural = switch points {
    | None => ""
    | Some(1) => ""
    | Some(_) => "s"
  };
  {
    ...component,
    render: (_self) =>
      <article className={cn("article")}>
        <span className={cn("index")}>{textEl(index)}</span>
        <div className={cn("metadata")}>
          <h2>
            { switch url {
              | None => textEl(title)
              | Some(url) => <a href={url} className={cn("outboundLink")}>
                  {textEl(title)}
                </a>
              }
            }
          </h2>
          <p>
            { switch points {
              | None => ReasonReact.nullElement
              | Some(points) => textEl({j|$points point$points_plural|j})
              }
            }
            { switch user {
              | None => ReasonReact.nullElement
              | Some(_user) => textEl(" by ")
              }
            }
            { switch user {
              | None => ReasonReact.nullElement
              | Some(user) => <a href={j|/user/$user|j} className={cn("author")}>
                    {textEl(user)}
                  </a>
              }
            }
            {textEl(" " ++ time_ago)}
            <a href={j|/item/$id|j} className={cn("commentCount")}>
              { switch comments_count {
                | 0 => textEl("discuss")
                | _ => textEl({j|$comments_count comment$comments_plural|j})
                }
              }
            </a>
          </p>
        </div>
      </article>
    }
  }

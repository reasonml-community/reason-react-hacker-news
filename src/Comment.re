open Utils;
let styles = requireCSSModule("src/Comment.module.css");
let cn = (name) => className(styles, name);

/* let error = _ => switch Webapi.Dom.Window.navigator.onLine {
  | true => <Text text={"Unable to load comments."} />
  | false => <Text text={"Unable to load comments."} />
}; */

let component = ReasonReact.statelessComponent("Comment");
let make = (~descendants, ~data, ~error, ~kidsOnly, _children) => {
  {
    ...component,
    render: (_self) =>
    <div className={cn("comments")}>
      { switch error {
          | true => ReasonReact.nullElement
          | false => if (descendants > 0) {
              <h2 className={cn("numberOfComments")}>{textEl({j|$descendants comments|j})}</h2>
            } else {
              ReasonReact.nullElement
            }
        }
      }
      { switch error {
        | true => <Text text={Some("Unable to load comments.")} isComment={false} />
        | false =>  <section>
            /* <Comment data={data} kidsOnly={true} /> */
          </section>
        }
      }
    </div>
  }
}

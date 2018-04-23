open Utils;
let styles = requireCSSModule("src/Text.module.css");

let component = ReasonReact.statelessComponent("Text");
let make = (~text, ~isComment, _children) => {
  {
    ...component,
    render: (_self) =>
      switch text {
      | None => ReasonReact.nullElement
      | Some(value) => <div
        className={classNameFilter(styles, [|
          ("text", true),
          ("comment", isComment)
        |])}
        dangerouslySetInnerHTML=(dangerousHtml(value))
        />
      }
  }
}

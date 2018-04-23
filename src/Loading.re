open Utils;
let styles = requireCSSModule("src/Loading.module.css");

let component = ReasonReact.statelessComponent("Loading");
let make = (_children) => {
  {
    ...component,
    render: (_self) =>
      <div className={className(styles, "routeLoading")}>
        <Logo width={"60"} height={"60"} />
      </div>
  }
}
